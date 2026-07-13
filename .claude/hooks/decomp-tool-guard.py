#!/usr/bin/env python3
"""PreToolUse guard for the lcu-match decomp loop.

Deterministically blocks the two shell footguns that look like a hang and burn a
weak model's whole session (observed with SWE-1.7 on Devin):

  a) paging/dumping a COMPILED BINARY (`tools/check`, `toolchain/bin/*`, `dc.py`)
     with head/cat/tail/less/more/xxd/strings/od/hexdump -> spews binary garbage
     into the context window.
  b) running BARE `tools/check` with no symbol -> checks all ~26,000 functions
     (many minutes; looks frozen). One symbol at a time is the rule.

Both Claude Code and the Devin CLI read `.claude/settings.json` hooks and pass
the tool call as JSON on stdin.

  * In **Claude Code** an `exit 2` block is a soft steer: the reason is fed back
    to the model, which retries with a corrected command.
  * In the **Devin CLI** a PreToolUse block is NOT relayed in non-interactive
    (`--print`) runs — it surfaces as "A tool was rejected by the user" and
    ABORTS the whole session (fatal). So under Devin we must NOT `exit 2`; we
    print the guidance and fail open (`exit 0`), letting the loop prompt and the
    per-iteration timeout be the footgun backstop instead.

Harness detection: Claude Code sends `tool_name` "Bash"; the Devin CLI sends
"exec" (and sets `DEVIN_*` env vars). Either marker => treat as Devin.

Fail-open: any parse problem or unexpected shape -> exit 0 (allow). A guard must
never wedge the agent on legitimate commands.
"""
import json
import os
import re
import shlex
import sys


def _under_devin(tool_name):
    """Devin CLI (block is fatal in --print) vs Claude Code (block is a soft steer)."""
    return tool_name == "exec" or any(
        os.environ.get(k)
        for k in ("DEVIN_PROJECT_DIR", "DEVIN_MODEL", "DEVIN_PERMISSION_MODE")
    )


def allow():
    sys.exit(0)


def block(reason, devin=False):
    if devin:
        # A block would abort the whole Devin session -> fail open, just steer.
        print(reason, file=sys.stderr)
        sys.exit(0)
    # Claude Code: stdout JSON + stderr + exit 2 is the soft-steer block.
    print(json.dumps({"decision": "block", "reason": reason}))
    print(reason, file=sys.stderr)
    sys.exit(2)


def main():
    try:
        data = json.load(sys.stdin)
    except Exception:
        allow()

    devin = _under_devin(data.get("tool_name", ""))

    cmd = (data.get("tool_input") or {}).get("command")
    if not isinstance(cmd, str) or not cmd.strip():
        allow()  # not a shell command (file read, etc.)

    # (a) reader/dumper aimed at a known compiled binary.
    if re.search(
        r"\b(head|cat|tail|less|more|xxd|strings|od|hexdump)\b[^|;&\n]*"
        r"(tools/check\b|toolchain/bin/|dc\.py\b)",
        cmd,
    ):
        block(
            "Blocked: `tools/check`, `toolchain/bin/*` and `dc.py` are COMPILED "
            "BINARIES — don't head/cat/less/more them (it dumps garbage into your "
            "context). Run them instead; `tools/check --help` shows usage. "
            "(lcu-match SKILL.md rule 7a)",
            devin,
        )

    # (b) bare `tools/check` with no positional symbol -> whole-tree (~26k) sweep.
    for seg in re.split(r"[;&|\n]+", cmd):
        m = re.search(r"(?:^|\s)(?:\./)?tools/check\b(.*)$", seg)
        if not m:
            continue
        try:
            toks = shlex.split(m.group(1)) if m.group(1).strip() else []
        except Exception:
            break  # unparseable segment -> don't second-guess it
        positional, skip_next = [], False
        for t in toks:
            if skip_next:
                skip_next = False
                continue
            if t == "--version":  # consumes its value
                skip_next = True
                continue
            if t.startswith("-"):
                continue
            positional.append(t)
        if not positional:
            block(
                "Blocked: bare `tools/check` with no symbol checks ALL ~26,000 "
                "functions (many minutes; looks frozen). Verify one function: "
                "`tools/check <MangledSymbol>`. (lcu-match SKILL.md rule 7b)",
                devin,
            )

    allow()


if __name__ == "__main__":
    main()

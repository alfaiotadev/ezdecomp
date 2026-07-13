# Lego City Undercover Decompilation

[Code Progress]: https://decomp.dev/projects/1065912392.svg?mode=shield&measure=code&label=Code&version=1.0.3

[Function Progress]: https://decomp.dev/projects/1065912392.svg?mode=shield&measure=matched_functions&label=Functions&version=1.0.3

[progress]: https://decomp.dev/Nintendocustom/Lego-City-Undercover-Decompilation

[Discord Badge]: https://img.shields.io/discord/1437530203411714191?color=%237289DA&logo=discord&logoColor=%23FFFFFF

[discord]: https://discord.com/invite/AyFjHz5EaT

**This repository does not contain game assets and cannot be used to play the game.**

## 🎯 The real deadline

Rockstar says *Grand Theft Auto VI* hits consoles on **19 October 2026** (PC port: "eventually"™️).
So the completely serious, not-at-all-tongue-in-cheek goal is to get this decomp **fully matched
before GTA VI ships** — so while everyone else is still waiting on the PC port, we're already
building on native source. And if the community is *really* fast: someone spins up a proper
modding framework, and we get, say, an **online multiplayer** feature dropped into LEGO City
before you can even boot Vice City. 🚔🧱

(Yes, this is a LEGO City Undercover decomp. Yes, we know how that sounds. Let us dream.)

## Resources
This project requires a `main` dumped from the latest *Lego City Undercover - EU* update, v1.0.3
(The US version 1.0.2 likely also works for decompilation, but is untested and has a different file hash).
The Japanese version isn't currently supported, because it was compiled with a different/unknown compiler version
similar to the other 1.0.0 versions.

# How to help

**You don't need the game, a binary, or any local setup** — anyone with a browser and
an LLM can contribute a byte-exact match:

1. Pick an [open issue](https://github.com/alfaiotadev/ezdecomp/issues?q=is%3Aissue+is%3Aopen+label%3Aopen)
   (labelled `open` / `good-first-function`) — each links a ready-made
   [decomp.me](https://decomp.me) scratch.
2. Comment `/claim`, open the scratch, and iterate C++ with any LLM until the diff hits **100%**.
3. Open a PR with your source and the scratch link. decomp.me compiles + diffs on its
   server, so no binary is needed to prove the match.

Full guide: [CONTRIBUTING.md](docs/CONTRIBUTING.md) (browser path + a local byte-verified
path for power users). You can also improve readability or fix non-matching functions.

# Todo
- fix lint.py
- create a file structure for the functions/classes based on the symbols
- Code style guidelines
- (if possible) improve progress tracking

## Why Nintendo Switch Edition?
The Nintendo Switch Edition has symbols, making it a good base for decompilation. The Wii U Edition doesn't have symbols
and the compiler toolchain GHS is abysmal. The chance that we find a matching compiler version is next to none, so our
assembly wouldn't be matching either way.

The Nintendo Switch Edition on the other hand was compiled with Clang where it's easier to find the compiler version just by the release date of the game.


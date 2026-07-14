#!/usr/bin/env python3
# Re-append the umbrella_engine.cpp entry to build/compile_commands.json (cmake wipes it
# on reconfigure). Idempotent. Run before seeding U functions with the engine umbrella.
import json, shlex, sys, os
DB = "/workspace/build/compile_commands.json"
U = "/home/decomp/umbrella_engine.cpp"
db = json.load(open(DB))
if any("umbrella_engine" in e["file"] for e in db):
    print("umbrella entry already present"); sys.exit(0)
base = db[0]; cmd = base.get("command") or " ".join(base.get("arguments", []))
args = shlex.split(cmd); out = []; skip = False
for a in args:
    if skip: skip = False; out.append(a); continue
    if a == "-o": out.append(a); skip = True; continue
    if a.endswith(".cpp"): out.append(U); continue
    out.append(a)
db.append({"directory": "/workspace", "command": " ".join(shlex.quote(x) for x in out), "file": U})
json.dump(db, open(DB, "w"))
print("umbrella entry appended")

# Decompilers

## IDA Pro

1. Install `nxo64.py` from
   `reswitched/loaders`.  [Instructions](https://github.com/reswitched/loaders?tab=readme-ov-file#installation)
2. Open `ida64.exe` and disassemble `main.nso`.

## Ghidra

### Setup Instructions

1. Setup [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases/latest). Some users have reported
   issues with the latest version, so try [this](https://github.com/RootCubed/ghidra-ci/releases/tag/2025-04-25) version
   if
   you encounter any issues.
2. Setup [Ghidra Switch Loader](https://github.com/Adubbz/Ghidra-Switch-Loader).
3. Create a new project. When importing `main.nso`, click `Options`. Then set `Base Address` to `0x7100000000`.
4. Analyze the binary (default options should be fine).

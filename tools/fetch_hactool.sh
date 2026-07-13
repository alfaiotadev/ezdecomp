#!/usr/bin/env bash
# Build hactool from source into tools/bin/hactool (native — no emulation).
# hactool is a small C tool (needs OpenSSL); it builds natively on arm64
# (Linux/macOS). Used by tools/extract_main.py to pull `main` out of the NSPs.
#
# Override the source ref with HACTOOL_REF (branch/tag). Re-run to rebuild.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN_DIR="$REPO_ROOT/tools/bin"
mkdir -p "$BIN_DIR"

if [ -x "$BIN_DIR/hactool" ] && [ "${FORCE:-0}" != "1" ]; then
  echo ">>> hactool already built: $BIN_DIR/hactool (FORCE=1 to rebuild)"
  exit 0
fi

REF="${HACTOOL_REF:-1.4.0}"
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

echo ">>> Cloning hactool (ref: $REF)..."
if ! git clone --depth 1 --branch "$REF" https://github.com/SciresM/hactool "$tmp/hactool" 2>/dev/null; then
  echo ">>> tag $REF not found, falling back to default branch"
  git clone --depth 1 https://github.com/SciresM/hactool "$tmp/hactool"
fi

cd "$tmp/hactool"
cp config.mk.template config.mk

jobs="$( (command -v nproc >/dev/null && nproc) || sysctl -n hw.ncpu 2>/dev/null || echo 4)"
echo ">>> Building hactool (-j$jobs)..."
make -j"$jobs"

install -m 0755 hactool "$BIN_DIR/hactool"
echo ">>> Installed: $BIN_DIR/hactool"
"$BIN_DIR/hactool" --help >/dev/null 2>&1 || true

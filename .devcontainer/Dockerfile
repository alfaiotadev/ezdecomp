# syntax=docker/dockerfile:1
#
# Lego City Undercover (Nintendo Switch) decomp toolchain.
#
# Dev machine: Apple Silicon Mac (arm64). This image is built and run as
# linux/arm64 — it runs NATIVELY on Apple Silicon, with NO Rosetta 2 and NO
# qemu/binfmt emulation.
#
# Why this works natively (unlike the Soul Sacrifice Delta project, which is
# pinned to linux/amd64 because vitasdk only ships an x86_64 prebuilt):
# LCU cross-compiles to `aarch64-linux-elf` using a prebuilt Clang 3.9.1 that
# the LCUDecompToolsCache release publishes for THREE hosts:
#   - LCUDecomp-binaries_aarch64-Linux.tar.xz   <- used by THIS arm64 container
#   - LCUDecomp-binaries_arm64-Darwin.tar.xz    <- native macOS host build
#   - LCUDecomp-binaries_x86_64-Linux.tar.xz
# `tools/setup.py` picks the host build via `{platform.machine()}-{platform.system()}`,
# which resolves to `aarch64-Linux` inside this container. The matching target is
# `aarch64-linux-elf` regardless of host arch, so host architecture does not
# affect matching — only whether the toolchain binaries run without emulation.
#
# Versions are pinned on purpose: matching decomp is sensitive to toolchain
# versions. Do not bump these lightly — a version change can break already
# matched functions (see AGENTS.md).
#
# Base: Ubuntu 24.04 (noble). The native aarch64-Linux prebuilt Clang 3.9.1
# requires glibc >= 2.38 and links libtinfo.so.6 — jammy (glibc 2.35) is too
# old, and jammy's libtinfo5 is the WRONG lib. Noble has glibc 2.39 + libtinfo6.
# (This mirrors why the Vita project needed Debian trixie for a new-enough glibc.)

FROM --platform=linux/arm64 ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

# --- Base build + decomp dependencies ----------------------------------------
# libtinfo6: runtime dep of the prebuilt Clang 3.9.1 (confirmed via ldd).
# llvm: provides llvm-objdump used by the diff/check tooling.
# ccache + ninja: fast rebuilds. xdelta3: used by some setup paths.
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential cmake ninja-build ccache \
      git curl wget unzip xz-utils ca-certificates sudo \
      python3 python3-pip python3-venv python-is-python3 \
      libssl-dev libtinfo6 \
      llvm xdelta3 \
    && rm -rf /var/lib/apt/lists/*

# --- Python tooling (decomp + progress scripts) -------------------------------
# clang-format is pinned to the v20 series to match the repo's .clang-format
# (which targets clang-format 20) and the lint workflow.
# --break-system-packages: noble marks the system env externally-managed (PEP668).
RUN pip3 install --no-cache-dir --break-system-packages \
      capstone colorama cxxfilt pyelftools ansiwrap watchdog \
      python-Levenshtein toml pyyaml protobuf gitpython \
      "clang-format~=20.1"

# --- Non-root user ------------------------------------------------------------
RUN useradd -m -s /bin/bash decomp && \
    echo "decomp ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/decomp

USER decomp
WORKDIR /workspace

CMD ["bash"]

# Building

The decomp toolchain was created for Linux & MacOS. While it isn't a hard requirement, if you're running Windows its
advised that you [setup WSL](https://learn.microsoft.com/en-us/windows/wsl/install) with an Ubuntu-like distro for the
easiest setup.
The setup should take less than 10 minutes if you follow the instructions below, except for dumping the game's
executable, which may take longer depending on your familiarity with homebrew and dumping games.

## Using the devcontainer (recommended on macOS / Apple Silicon)

A ready-to-use dev container is provided in [`.devcontainer/`](../.devcontainer). On an Apple Silicon Mac it runs
**natively as `linux/arm64` — no Rosetta 2 and no qemu emulation**. This works because the toolchain cache ships a
native `aarch64-Linux` build of Clang 3.9.1, which `tools/setup.py` selects automatically; the matching target is
`aarch64-linux-elf` regardless of host architecture.

1. Install a Docker provider and the VS Code **Dev Containers** extension. On
   Apple Silicon, **[OrbStack](https://orbstack.dev)** is recommended — it runs
   native arm64 Linux containers (no Rosetta/qemu) and is a drop-in `docker` /
   `docker compose` replacement; Docker Desktop works too. VS Code Dev Containers
   uses whichever is your active Docker context.
2. Open the repo in VS Code → **Dev Containers: Reopen in Container**.
3. The first build installs OS dependencies; `postCreate` runs `tools/setup.py --project-only` to download the pinned
   toolchain and create `build/`.
4. To add the game binary (clean-room — you provide your own legal dump), run inside the container:
   `tools/setup.py /path/to/main` (EU v1.0.3 `main` NSO). If you only have the NSP dump, extract `main`
   first with `tools/extract_main.py` — see [EXTRACTING.md](EXTRACTING.md).

The container mounts your local `.env` (for the GitHub API token); that file stays gitignored and never enters the
image. If you don't use the GitHub API, remove the `--env-file` entry from `.devcontainer/devcontainer.json`.

The rest of this document covers a manual (non-container) setup.

## For Windows users

If you're using Windows, it's highly recommended to use WSL (Windows Subsystem for Linux) with an Ubuntu-like
distribution for the best compatibility.
Follow the [official Microsoft guide](https://learn.microsoft.com/en-us/windows/wsl/install) to set up WSL on your
system, or just run `wsl --install` in an elevated PowerShell terminal if you're on Windows 11.
Once WSL is installed, you can follow the Linux instructions below within your WSL environment.
Now you can go on with the steps below.

## 1. Set up dependencies

* Python 3.6 or newer with [pip](https://pip.pypa.io/en/stable/installation/)
* Ninja
* CMake 3.13+
    * If you are on Ubuntu 18.04, you must
      first [update CMake by using the official CMake APT repository](https://apt.kitware.com/).
* ccache (to speed up builds)
* llvm-objdump

Ubuntu users can install those dependencies by running:

```shell
sudo apt install python3 ninja-build cmake ccache libssl-dev libncurses5 llvm
```

If you are running Ubuntu 23.10 or later, the `libncurses5` package won't be available anymore. You can install it from
the archive using:

```shell
wget http://archive.ubuntu.com/ubuntu/pool/universe/n/ncurses/libtinfo5_6.3-2_amd64.deb && sudo dpkg -i libtinfo5_6.3-2_amd64.deb && rm -f libtinfo5_6.3-2_amd64.deb
```

For other systems, please check for the corresponding `libncurses5` backport, for
example [ncurses5-compat-libs](https://aur.archlinux.org/packages/ncurses5-compat-libs) for Arch-based distributions.

Additionally, you'll also need:

* The following Python modules that can be installed with the following command:
  `pip install capstone colorama cxxfilt pyelftools ansiwrap watchdog python-Levenshtein toml pyyaml`

## 2. Set up the project

1. Clone this repository. If you are using WSL, please clone the repo *inside* WSL, *not* on the Windows side (for performance reasons).
   Run `git clone --recurse-submodules https://github.com/Nintendocustom/Lego-City-Undercover-Decompilation.git`

2. Acquire the **original v1.0.3 EU `main` NSO executable** using
   the [Dumping guide](https://zeldamods.org/wiki/Help:Dumping_games#Switch).
3. Run `python3 tools/setup.py [path to the NSO]`
    * This will:
        * install tools/check to check for differences in decompiled code
        * convert the executable if necessary
      * set up [Clang 3.9.1](https://releases.llvm.org/download.html#3.9.1)
        * create a build directory in `build/`
    * If something goes wrong, follow the instructions given to you by the script.
    * If you wish to use a CMake generator that isn't Ninja, use `--cmake_backend` to specify it.

## 3. Build

To start the build, just run

```shell
python3 tools/build.py
```

By default, a multithreaded build is performed.

To check whether everything built correctly, just run `tools/check` after the build completes.

You can check the current progress with `python3 tools/common/progress.py`.

## 4. Decompilers

For instructions on setting up a decompiler, see [DECOMPILERS.md](DECOMPILERS.md).

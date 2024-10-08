#!/bin/bash -e

# Run script in project root
ROOT="$(git rev-parse --show-toplevel)"
cd $ROOT
sudo apt-get update

# Installs python virtual environment and activates it, NB: run 'deactivate' to exit
sudo apt-get install -y \
  python3.12 \
  python3.12-venv
python3.12 -m venv venv
source venv/bin/activate
pip3 install --upgrade scons

# Packages specified here
# https://docs.godotengine.org/en/stable/contributing/development/compiling/compiling_for_linuxbsd.html
sudo apt-get install -y \
  build-essential \
  pkg-config \
  libx11-dev \
  libxcursor-dev \
  libxinerama-dev \
  libgl1-mesa-dev \
  libglu1-mesa-dev \
  libasound2-dev \
  libpulse-dev \
  libudev-dev \
  libxi-dev \
  libxrandr-dev \
  libwayland-dev

# Init submodules, but not recursively. 
# We remove godot-cpp as a submodule for godot plugins we compile from source,
# since we will use the common godot-cpp version from PROJECT_ROOT/godot-cpp
# No need to recursively fetch submodules in that case
git submodule init

# go back to previous directory
cd -
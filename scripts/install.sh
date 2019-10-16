#!/usr/bin/env bash

python -m install conan
mkdir build
conan install . -if build

sudo apt-get install libprotobuf-dev protobuf-compiler

git clone --recurse-submodules https://github.com/inphos42/osmpbf/

#!/usr/bin/env bash

python3 -m pip install virtualenv
python3 -m virtualenv venv/ -p python3
. ./venv/bin/activate

python3 -m pip install -r requirements.txt

mkdir build
conan install . -if build

deactivate ./venv/bin/

sudo apt-get install libprotobuf-dev protobuf-compiler libqt5webengine5 libqt5widgets5 qtwebengine5-dev

git clone --recurse-submodules https://github.com/inphos42/osmpbf/

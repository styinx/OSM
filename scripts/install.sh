#!/usr/bin/env bash

python3 -m pip install virtualenv
python3 -m virtualenv venv/ -p python3
. ./venv/bin/activate

python3 -m pip install -r requirements.txt

mkdir build
conan install . -if build

deactivate ./venv/bin/

sudo apt-get install libgtest-dev libprotobuf-dev protobuf-compiler libqt5webengine5 libqt5widgets5 qtwebengine5-dev

# fix for gtest
sudo wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
sudo tar xf release-1.8.0.tar.gz
cd googletest-release-1.8.0
sudo cmake -DBUILD_SHARED_LIBS=ON .
sudo make
sudo cp -a include/gtest /usr/include
sudo cp -a libgtest_main.so libgtest.so /usr/lib/

git clone --recurse-submodules https://github.com/inphos42/osmpbf/

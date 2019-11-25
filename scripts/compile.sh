#!/usr/bin/env bash

cd osmpbf
mkdir build
cd build
make clean
cmake .. && make
cd ../..

cd build
cmake .. && make
cd ..

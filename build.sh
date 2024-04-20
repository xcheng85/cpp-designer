#!/bin/bash
clear;

# check build dir
if [ ! -d build ] 
then 
    mkdir build 
fi

# generate cmake files
cmake -B ./build -S . -DCMAKE_BUILD_TYPE=Debug

# compile project
cmake --build ./build

echo compilation completed!

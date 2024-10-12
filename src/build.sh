#!/bin/bash

rm -rf build/*
conan install . --output-folder=build --build=missing
cmake -S . -B build
make -C build

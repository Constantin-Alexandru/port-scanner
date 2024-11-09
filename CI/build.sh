#! /bin/bash

# Clean and regenerate build folder
rm -R build
mkdir build
cd build

# Generate executable
cmake ..
make



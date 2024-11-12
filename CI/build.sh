#! /bin/bash

# Define generator
GENERATOR="Unix Makefiles"
GENERATOR_COMMAND="make"

# Define the build folder
BUILD_DIR="build"

# Remove the current build folder if it exists
if [ -d "$BUILD_DIR" ]; then
  echo "Deleting existing build directory..."
  rm -rf "$BUILD_DIR"
fi

# Create build directory
echo "Creating new build directory ($BUILD_DIR)..."
mkdir "$BUILD_DIR"

# Change to the build directory
cd "$BUILD_DIR"

# Run CMake
echo "Generating source with generator: $GENERATOR..."
cmake .. -G "$GENERATOR"


# Run the generator
echo Compiling project with: $GENERATOR_COMMAND...
$GENERATOR_COMMAND


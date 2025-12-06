#!/bin/bash

set -e

BUILD_DIR="build"
TEST_EXEC="$BUILD_DIR/vector_tests"

if [ ! -f "$TEST_EXEC" ]; then
    echo "Test executable not found. Building project..."
    ./build.sh
fi

echo "Running tests with GoogleTest verbose output..."
"$TEST_EXEC" --gtest_color=yes 

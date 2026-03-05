#!/bin/bash
set -e

find . -type f \( -name "*.hpp" -o -name "*.cpp" -o -name "*.cu" -o -name "*.cuh" \) -print0 | \
    xargs -0 clang-format -i

echo "Formatting completed!"

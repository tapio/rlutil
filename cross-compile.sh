#!/bin/sh
# Script name: build-mingw.sh
# Description: builds examples with migw32 cross-compiler

FLAGS="-Wall -Wextra"
CROSSPREFIX="i686-pc-mingw32-"

${CROSSPREFIX}g++ $FLAGS test.cpp -o test.exe || exit 1

${CROSSPREFIX}g++ $FLAGS example.cpp -o example-cpp.exe || exit 1

${CROSSPREFIX}gcc $FLAGS example.c -o example-c.exe || exit 1


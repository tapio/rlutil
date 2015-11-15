#!/bin/sh
# Script name: build-mingw.sh
# Description: builds examples with mingw32 cross-compiler

FLAGS="-Wall -Wextra -g"
CROSSPREFIX="i686-w64-mingw32.static-"
#CROSSPREFIX="i686-pc-mingw32-"

${CROSSPREFIX}g++ $FLAGS test.cpp -o test.exe || exit 1

${CROSSPREFIX}gcc $FLAGS example.c -o example-c.exe || exit 1


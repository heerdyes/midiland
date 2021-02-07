#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

pushd txtmidi
gcc $1.c -lglut -lGL -lGLU -lm -o ../bin/$1
popd
prog=$1
shift
./bin/$prog "$@"


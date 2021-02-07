#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

gcc $1.c -lglut -lGL -lGLU -lm -o $1
prog=$1
shift
./$prog "$@"


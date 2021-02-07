#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

prog=$1
shift
./bin/$prog "$@"


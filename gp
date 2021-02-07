#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

python3 seqgen.py $1.hook $1.seq
./cr sequencer_00 $1.seq $2


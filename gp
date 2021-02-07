#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

python3 composer/seqgen.py hook/$1.hook seq/$1.seq
./cr sequencer_00 seq/$1.seq $2


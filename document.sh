#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

$SCRIPT_DIR/packages/simple-documentation-library/document.py containers 1.2.1 "Simple containers library in C" source documentation
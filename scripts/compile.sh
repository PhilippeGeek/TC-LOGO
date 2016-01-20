#!/bin/bash

OUT=$2 || "`dirname $1`/`basename $1 .logo`.svg"
IN=$1
logo="logo"
if [ -e $(dirname $0)/../bin/logo ]; then
    logo="$(dirname $0)/../bin/logo";
fi;

echo "Compile $IN to $OUT";
$logo < $IN > $OUT;
if [ "$(uname)" == "Darwin" ]; then open $OUT; echo "Opened"; fi;
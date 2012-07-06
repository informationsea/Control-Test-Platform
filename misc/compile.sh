#!/bin/sh

source ./environment.sh

if [ -f /usr/bin/clang ];then
    USE_CLANG=1
    export USE_CLANG
fi

for i in `find . -name "Makefile" -mindepth 2`; do
    make -C `dirname $i` "$@"
done

#!/bin/bash

export array1=("depcomp" "missing" "COPYING" "INSTALL" \
  "aclocal.m4" "autom4te.cache" "stamp-h1" "config.status" \
  "config.h" "config.h.in" "config.log" \
  "ltmain.sh m4" "config.h.in~" "ar-lib" "libtool" "Makefile.in" \
  "config.guess" "config.log" "config.status" "config.sub" "configure" \
  "install-sh")

for i in "${array1[@]}";
do
    rm -rf ${i};
done

export array2=(NEWS README AUTHORS ChangeLog)
for i in "${array2[@]}";
do
    rm -rf ${i};
done

rm -f compile

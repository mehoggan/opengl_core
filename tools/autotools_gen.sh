#!/bin/bash

export array1=("depcomp" "install-sh" "missing" "COPYING" "INSTALL")
for i in "${array1[@]}";
do
    cp "/usr/share/automake-1.13/"${i} ./;
done

export array2=(NEWS README AUTHORS ChangeLog)
for i in "${array2[@]}";
do
    touch ${i};
done

if [ ! -d m4 ];
then
  mkdir m4
fi

aclocal && autoconf && autoreconf --no-recursive --install && autoheader && libtoolize && \
  automake --add-missing

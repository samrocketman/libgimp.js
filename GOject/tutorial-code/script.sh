#!/bin/bash

make clean

make all

g-ir-scanner tut-greeter.[ch] \
    --program=./greeter \
    `pkg-config --cflags gobject-introspection-1.0` --include=GObject-2.0 \
    --namespace=Tut --nsversion=0.1 --output=Tut-0.1.gir

g-ir-compiler Tut-0.1.gir --output=Tut-0.1.typelib

export GI_TYPELIB_PATH=`pwd`
./greeter main.js

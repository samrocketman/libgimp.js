#!/bin/bash

make clean

make all

g-ir-scanner js-greeter.[ch] \
    --program=./greeter \
    `pkg-config --cflags gobject-introspection-1.0` --include=GObject-2.0 \
    --namespace=Js --nsversion=0.1 --output=Js-0.1.gir

g-ir-compiler Js-0.1.gir --output=Js-0.1.typelib

export GI_TYPELIB_PATH=`pwd`
./greeter main.js

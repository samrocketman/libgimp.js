#
# GOBject Introspection Tutorial 
# 
# Written in 2013 by Simon Kågedal Reimer <skagedal@gmail.com>
#
# To the extent possible under law, the author have dedicated all
# copyright and related and neighboring rights to this software to
# the public domain worldwide. This software is distributed without
# any warranty.
#
# CC0 Public Domain Dedication:
# http://creativecommons.org/publicdomain/zero/1.0/

CFLAGS=`pkg-config --cflags glib-2.0 gobject-2.0 gobject-introspection-1.0 gjs-1.0` -g 
LIBS=`pkg-config --libs glib-2.0 gobject-2.0 gobject-introspection-1.0 gjs-1.0` 

OBJECTS=js-plugin.o main.o
SOURCES=js-plugin.c js-plugin.h main.c

all: greeter

greeter: $(OBJECTS)	
	$(CC) -o $@ $(OBJECTS) $(LIBS)

js-plugin.o: js-plugin.c js-plugin.h
main.o: main.c js-plugin.h

clean:
	rm *.o greeter

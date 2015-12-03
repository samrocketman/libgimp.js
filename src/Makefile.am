## Process this file with automake to produce Makefile.in

bin_PROGRAMS = script-js

bindir = $(GIMP_LIBDIR)/plug-ins

script_js_SOURCES = \
	plugin-intl.h	\
	interface.c	\
	interface.h	\
	main.c		\
	main.h		\
	render.c	\
	render.h

AM_CPPFLAGS = \
	-DLOCALEDIR=\""$(LOCALEDIR)"\"		\
	-DDATADIR=\""$(DATADIR)"\"

*_CPPFLAGS =\
	-I$(top_srcdir)		\
	@GIMP_CFLAGS@		\
	-I$(includedir)

LDADD = $(GIMP_LIBS)


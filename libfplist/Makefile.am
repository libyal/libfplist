AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@

lib_LTLIBRARIES = libfplist.la

libfplist_la_SOURCES = \
	libfplist.c \
	libfplist_definitions.h \
	libfplist_extern.h \
	libfplist_error.c libfplist_error.h \
	libfplist_key.c libfplist_key.h \
	libfplist_libcerror.h \
	libfplist_libcstring.h \
	libfplist_support.c libfplist_support.h \
	libfplist_types.h \
	libfplist_unused.h

libfplist_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@

libfplist_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libfplist_definitions.h.in \
	libfplist.rc \
	libfplist.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libfplist_definitions.h
	/bin/rm -f libfplist.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libfplist ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfplist_la_SOURCES)


AM_LFLAGS = -Cf
AM_YFLAGS = -d -v -l -p xml_scanner_

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@

BUILT_SOURCES = libfplist_xml_parser.h

lib_LTLIBRARIES = libfplist.la

libfplist_la_SOURCES = \
	libfplist.c \
	libfplist_definitions.h \
	libfplist_extern.h \
	libfplist_error.c libfplist_error.h \
	libfplist_key.c libfplist_key.h \
	libfplist_libcdata.h \
	libfplist_libcerror.h \
	libfplist_libcnotify.h \
	libfplist_libcstring.h \
	libfplist_libfguid.h \
	libfplist_libfvalue.h \
	libfplist_libuna.h \
	libfplist_plist.c libfplist_plist.h \
	libfplist_support.c libfplist_support.h \
	libfplist_types.h \
	libfplist_unused.h \
	libfplist_xml_attribute.c libfplist_xml_attribute.h \
	libfplist_xml_parser.y \
	libfplist_xml_scanner.l \
	libfplist_xml_tag.c libfplist_xml_tag.h

libfplist_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFVALUE_LIBADD@

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


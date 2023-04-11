AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFPLIST_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fplist_test_error \
	fplist_test_property \
	fplist_test_property_list \
	fplist_test_support \
	fplist_test_xml_attribute \
	fplist_test_xml_parser \
	fplist_test_xml_tag

fplist_test_error_SOURCES = \
	fplist_test_error.c \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_unused.h

fplist_test_error_LDADD = \
	../libfplist/libfplist.la

fplist_test_property_SOURCES = \
	fplist_test_libcerror.h \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_memory.c fplist_test_memory.h \
	fplist_test_property.c \
	fplist_test_unused.h

fplist_test_property_LDADD = \
	../libfplist/libfplist.la \
	@LIBCERROR_LIBADD@

fplist_test_property_list_SOURCES = \
	fplist_test_libcerror.h \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_memory.c fplist_test_memory.h \
	fplist_test_property_list.c \
	fplist_test_unused.h

fplist_test_property_list_LDADD = \
	../libfplist/libfplist.la \
	@LIBCERROR_LIBADD@

fplist_test_support_SOURCES = \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_support.c \
	fplist_test_unused.h

fplist_test_support_LDADD = \
	../libfplist/libfplist.la

fplist_test_xml_attribute_SOURCES = \
	fplist_test_libcerror.h \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_memory.c fplist_test_memory.h \
	fplist_test_unused.h \
	fplist_test_xml_attribute.c

fplist_test_xml_attribute_LDADD = \
	../libfplist/libfplist.la \
	@LIBCERROR_LIBADD@

fplist_test_xml_parser_SOURCES = \
	fplist_test_libcerror.h \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_unused.h \
	fplist_test_xml_parser.c

fplist_test_xml_parser_LDADD = \
	../libfplist/libfplist.la \
	@LIBCERROR_LIBADD@

fplist_test_xml_tag_SOURCES = \
	fplist_test_libcerror.h \
	fplist_test_libfplist.h \
	fplist_test_macros.h \
	fplist_test_memory.c fplist_test_memory.h \
	fplist_test_unused.h \
	fplist_test_xml_tag.c

fplist_test_xml_tag_LDADD = \
	../libfplist/libfplist.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


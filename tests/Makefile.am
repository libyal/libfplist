AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFPLIST_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fplist_test_error \
	fplist_test_property \
	fplist_test_property_list \
	fplist_test_support

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

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


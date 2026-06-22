AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFPLIST_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: \
	package.m4 \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in


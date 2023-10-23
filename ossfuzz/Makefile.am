if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common

bin_PROGRAMS = \
	property_fuzzer \
	property_list_fuzzer

property_fuzzer_SOURCES = \
	ossfuzz_libfplist.h \
	property_fuzzer.cc

property_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfplist/libfplist.la

property_list_fuzzer_SOURCES = \
	ossfuzz_libfplist.h \
	property_list_fuzzer.cc

property_list_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfplist/libfplist.la
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

splint-local:
	@echo "Running splint on property_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(property_fuzzer_SOURCES)
	@echo "Running splint on property_list_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(property_list_fuzzer_SOURCES)


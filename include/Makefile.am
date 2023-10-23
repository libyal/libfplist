include_HEADERS = \
	libfplist.h

pkginclude_HEADERS = \
	libfplist/definitions.h \
	libfplist/error.h \
	libfplist/extern.h \
	libfplist/features.h \
	libfplist/types.h

EXTRA_DIST = \
	libfplist.h.in \
	libfplist/definitions.h.in \
	libfplist/features.h.in \
	libfplist/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfplist.h
	-rm -f libfplist/definitions.h
	-rm -f libfplist/features.h
	-rm -f libfplist/types.h
	-rm -f Makefile


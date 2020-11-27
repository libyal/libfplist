#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libfplist/.libs/libfplist.1.dylib && test -f ./pyfplist/.libs/pyfplist.so;
then
	install_name_tool -change /usr/local/lib/libfplist.1.dylib ${PWD}/libfplist/.libs/libfplist.1.dylib ./pyfplist/.libs/pyfplist.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};


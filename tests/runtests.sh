#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libfplist/.libs/libfplist.1.dylib && test -f ./pyfplist/.libs/pyfplist.so
then
	install_name_tool -change /usr/local/lib/libfplist.1.dylib ${PWD}/libfplist/.libs/libfplist.1.dylib ./pyfplist/.libs/pyfplist.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}


#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libfplist/.libs/libfplist.1.dylib" ] && [ -f ./pyfplist/.libs/pyfplist.so ]
then
    install_name_tool -change /usr/local/lib/libfplist.1.dylib "${PWD}/libfplist/.libs/libfplist.1.dylib" ./pyfplist/.libs/pyfplist.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}


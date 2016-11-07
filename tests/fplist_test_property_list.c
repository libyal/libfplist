/*
 * Library property list type testing program
 *
 * Copyright (C) 2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fplist_test_libcerror.h"
#include "fplist_test_libfplist.h"
#include "fplist_test_macros.h"
#include "fplist_test_memory.h"
#include "fplist_test_unused.h"

char *fplist_test_property_list_byte_stream = \
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
	"<plist version=\"1.0\">\n"
	"<dict>\n"
	"	<key>CFBundleInfoDictionaryVersion</key>\n"
	"	<string>6.0</string>\n"
	"	<key>band-size</key>\n"
	"	<integer>8388608</integer>\n"
	"	<key>bundle-backingstore-version</key>\n"
	"	<integer>1</integer>\n"
	"	<key>diskimage-bundle-type</key>\n"
	"	<string>com.apple.diskimage.sparsebundle</string>\n"
	"	<key>size</key>\n"
	"	<integer>102400000</integer>\n"
	"</dict>\n"
	"</plist>\n";

/* Tests the libfplist_property_list_initialize function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_list_initialize(
     void )
{
	libcerror_error_t *error                 = NULL;
	libfplist_property_list_t *property_list = NULL;
	int result                               = 0;

	/* Test libfplist_property_list_initialize
	 */
	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "property_list",
         property_list );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfplist_property_list_free(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "property_list",
         property_list );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfplist_property_list_initialize(
	          NULL,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	property_list = (libfplist_property_list_t *) 0x12345678UL;

	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	property_list = NULL;

#if defined( HAVE_FPLIST_TEST_MEMORY )

	/* Test libfplist_property_list_initialize with malloc failing
	 */
	fplist_test_malloc_attempts_before_fail = 0;

	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	if( fplist_test_malloc_attempts_before_fail != -1 )
	{
		fplist_test_malloc_attempts_before_fail = -1;

		if( property_list != NULL )
		{
			libfplist_property_list_free(
			 &property_list,
			 NULL );
		}
	}
	else
	{
		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FPLIST_TEST_ASSERT_IS_NULL(
		 "property_list",
		 property_list );

		FPLIST_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfplist_property_list_initialize with memset failing
	 */
	fplist_test_memset_attempts_before_fail = 0;

	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	if( fplist_test_memset_attempts_before_fail != -1 )
	{
		fplist_test_memset_attempts_before_fail = -1;

		if( property_list != NULL )
		{
			libfplist_property_list_free(
			 &property_list,
			 NULL );
		}
	}
	else
	{
		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FPLIST_TEST_ASSERT_IS_NULL(
		 "property_list",
		 property_list );

		FPLIST_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FPLIST_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( property_list != NULL )
	{
		libfplist_property_list_free(
		 &property_list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_list_free function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_list_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfplist_property_list_free(
	          NULL,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfplist_property_list_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_list_copy_from_byte_stream(
     void )
{
	libcerror_error_t *error                 = NULL;
	libfplist_property_list_t *property_list = NULL;
	int result                               = 0;

	/* Initialize test
	 */
	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "property_list",
         property_list );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test copy from byte stream
	 */
	result = libfplist_property_list_copy_from_byte_stream(
	          property_list,
	          (uint8_t *) fplist_test_property_list_byte_stream,
	          496,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libfplist_property_list_free(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Initialize test
	 */
	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "property_list",
         property_list );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfplist_property_list_copy_from_byte_stream(
	          NULL,
	          (uint8_t *) fplist_test_property_list_byte_stream,
	          496,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_list_copy_from_byte_stream(
	          property_list,
	          NULL,
	          496,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_list_copy_from_byte_stream(
	          property_list,
	          (uint8_t *) fplist_test_property_list_byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfplist_property_list_free(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( property_list != NULL )
	{
		libfplist_property_list_free(
		 &property_list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_list_has_plist_root_element function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_list_has_plist_root_element(
     void )
{
	libcerror_error_t *error                 = NULL;
	libfplist_property_list_t *property_list = NULL;
	int result                               = 0;

	/* Initialize test
	 */
	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "property_list",
         property_list );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfplist_property_list_copy_from_byte_stream(
	          property_list,
	          (uint8_t *) fplist_test_property_list_byte_stream,
	          496,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test determine if property list has plist root element
	 */
	result = libfplist_property_list_has_plist_root_element(
	          property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfplist_property_list_has_plist_root_element(
	          NULL,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfplist_property_list_free(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( property_list != NULL )
	{
		libfplist_property_list_free(
		 &property_list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_list_get_root_property function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_list_get_root_property(
     void )
{
	libcerror_error_t *error                 = NULL;
	libfplist_property_t *property           = NULL;
	libfplist_property_list_t *property_list = NULL;
	int result                               = 0;

	/* Initialize test
	 */
	result = libfplist_property_list_initialize(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "property_list",
         property_list );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfplist_property_list_copy_from_byte_stream(
	          property_list,
	          (uint8_t *) fplist_test_property_list_byte_stream,
	          496,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test retrieve root property
	 */
	result = libfplist_property_list_get_root_property(
	          property_list,
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "property",
         property );

	libfplist_property_free(
	 &property,
	 NULL );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfplist_property_list_get_root_property(
	          NULL,
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_list_get_root_property(
	          property_list,
	          NULL,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	property = (libfplist_property_t *) 0x12345678UL;

	result = libfplist_property_list_get_root_property(
	          property_list,
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	property = NULL;

	/* Clean up
	 */
	result = libfplist_property_list_free(
	          &property_list,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( property_list != NULL )
	{
		libfplist_property_list_free(
		 &property_list,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FPLIST_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FPLIST_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FPLIST_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FPLIST_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FPLIST_TEST_UNREFERENCED_PARAMETER( argc )
	FPLIST_TEST_UNREFERENCED_PARAMETER( argv )

	FPLIST_TEST_RUN(
	 "libfplist_property_list_initialize",
	 fplist_test_property_list_initialize );

	FPLIST_TEST_RUN(
	 "libfplist_property_list_free",
	 fplist_test_property_list_free );

	FPLIST_TEST_RUN(
	 "libfplist_property_list_copy_from_byte_stream",
	 fplist_test_property_list_copy_from_byte_stream );

	FPLIST_TEST_RUN(
	 "ibfplist_property_list_has_plist_root_element",
	 fplist_test_property_list_has_plist_root_element );

	FPLIST_TEST_RUN(
	 "libfplist_property_list_get_root_property",
	 fplist_test_property_list_get_root_property );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


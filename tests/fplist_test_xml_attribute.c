/*
 * Library xml_attribute type test program
 *
 * Copyright (C) 2016-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

#include "../libfplist/libfplist_xml_attribute.h"

#if defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT )

/* Tests the libfplist_xml_attribute_initialize function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_attribute_initialize(
     void )
{
	libcerror_error_t *error                 = NULL;
	libfplist_xml_attribute_t *xml_attribute = NULL;
	int result                               = 0;

#if defined( HAVE_FPLIST_TEST_MEMORY )
	int number_of_malloc_fail_tests          = 3;
	int number_of_memset_fail_tests          = 1;
	int test_number                          = 0;

#if defined( OPTIMIZATION_DISABLED )
	int number_of_memcpy_fail_tests          = 2;
#endif
#endif /* defined( HAVE_FPLIST_TEST_MEMORY ) */

	/* Test regular cases
	 */
	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          4,
	          (uint8_t *) "value",
	          5,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_attribute",
	 xml_attribute );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_attribute_free(
	          &xml_attribute,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_attribute",
	 xml_attribute );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_xml_attribute_initialize(
	          NULL,
	          (uint8_t *) "name",
	          4,
	          (uint8_t *) "value",
	          5,
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

	xml_attribute = (libfplist_xml_attribute_t *) 0x12345678UL;

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          4,
	          (uint8_t *) "value",
	          5,
	          &error );

	xml_attribute = NULL;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          NULL,
	          4,
	          (uint8_t *) "value",
	          5,
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

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          (size_t) SSIZE_MAX,
	          (uint8_t *) "value",
	          5,
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

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          0,
	          (uint8_t *) "value",
	          5,
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

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          4,
	          NULL,
	          5,
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

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          4,
	          (uint8_t *) "value",
	          (size_t) SSIZE_MAX,
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

	result = libfplist_xml_attribute_initialize(
	          &xml_attribute,
	          (uint8_t *) "name",
	          4,
	          (uint8_t *) "value",
	          0,
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

#if defined( HAVE_FPLIST_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 * 2 fail in memory_allocate of name
	 * 3 fail in memory_allocate of value
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfplist_xml_attribute_initialize with malloc failing
		 */
		fplist_test_malloc_attempts_before_fail = test_number;

		result = libfplist_xml_attribute_initialize(
		          &xml_attribute,
		          (uint8_t *) "name",
		          4,
		          (uint8_t *) "value",
		          5,
		          &error );

		if( fplist_test_malloc_attempts_before_fail != -1 )
		{
			fplist_test_malloc_attempts_before_fail = -1;

			if( xml_attribute != NULL )
			{
				libfplist_xml_attribute_free(
				 &xml_attribute,
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
			 "xml_attribute",
			 xml_attribute );

			FPLIST_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfplist_xml_attribute_initialize with memset failing
		 */
		fplist_test_memset_attempts_before_fail = test_number;

		result = libfplist_xml_attribute_initialize(
		          &xml_attribute,
		          (uint8_t *) "name",
		          4,
		          (uint8_t *) "value",
		          5,
		          &error );

		if( fplist_test_memset_attempts_before_fail != -1 )
		{
			fplist_test_memset_attempts_before_fail = -1;

			if( xml_attribute != NULL )
			{
				libfplist_xml_attribute_free(
				 &xml_attribute,
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
			 "xml_attribute",
			 xml_attribute );

			FPLIST_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#if defined( OPTIMIZATION_DISABLED )
	/* 1 fail in memcpy after memory_allocate of name
	 */
	for( test_number = 0;
	     test_number < number_of_memcpy_fail_tests;
	     test_number++ )
	{
		/* Test libfplist_xml_attribute_initialize with memcpy failing
		 */
		fplist_test_memcpy_attempts_before_fail = test_number;

		result = libfplist_xml_attribute_initialize(
		          &xml_attribute,
		          (uint8_t *) "name",
		          4,
		          (uint8_t *) "value",
		          5,
		          &error );

		if( fplist_test_memcpy_attempts_before_fail != -1 )
		{
			fplist_test_memcpy_attempts_before_fail = -1;

			if( xml_attribute != NULL )
			{
				libfplist_xml_attribute_free(
				 &xml_attribute,
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
			 "xml_attribute",
			 xml_attribute );

			FPLIST_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_FPLIST_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( xml_attribute != NULL )
	{
		libfplist_xml_attribute_free(
		 &xml_attribute,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_attribute_free function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_attribute_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfplist_xml_attribute_free(
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

#endif /* defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT )

	FPLIST_TEST_RUN(
	 "libfplist_xml_attribute_initialize",
	 fplist_test_xml_attribute_initialize );

	FPLIST_TEST_RUN(
	 "libfplist_xml_attribute_free",
	 fplist_test_xml_attribute_free );

#endif /* defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


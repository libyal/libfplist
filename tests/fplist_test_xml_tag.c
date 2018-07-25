/*
 * Library xml_tag type test program
 *
 * Copyright (C) 2016-2018, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libfplist/libfplist_xml_tag.h"

typedef struct fplist_test_xml_tag_value_type_test fplist_test_xml_tag_value_type_test_t;

struct fplist_test_xml_tag_value_type_test
{
        /* The value type
         */
        int value_type;

        /* The XML tag name
         */
        const char *tag_name;

        /* The XML tag name length
         */
        size_t tag_name_length;
};

#if defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT )

/* Tests the libfplist_xml_tag_initialize function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfplist_xml_tag_t *xml_tag    = NULL;
	int result                      = 0;

#if defined( HAVE_FPLIST_TEST_MEMORY )
	int number_of_malloc_fail_tests = 5;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;

#if defined( OPTIMIZATION_DISABLED )
	int number_of_memcpy_fail_tests = 1;
#endif
#endif /* defined( HAVE_FPLIST_TEST_MEMORY ) */

	/* Test regular cases
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_xml_tag_initialize(
	          NULL,
	          (uint8_t *) "data",
	          4,
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

	xml_tag = (libfplist_xml_tag_t *) 0x12345678UL;

	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	xml_tag = NULL;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          NULL,
	          4,
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

	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
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

	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
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
	 * 3 fail in memory_allocate_structure of libcdata_array_initialize of attributes array
	 * 4 fail in memory_allocate of libcdata_array_initialize of attributes array entries
	 * 5 fail in memory_allocate_structure of libcdata_array_initialize of elements array
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfplist_xml_tag_initialize with malloc failing
		 */
		fplist_test_malloc_attempts_before_fail = test_number;

		result = libfplist_xml_tag_initialize(
		          &xml_tag,
		          (uint8_t *) "data",
		          4,
		          &error );

		if( fplist_test_malloc_attempts_before_fail != -1 )
		{
			fplist_test_malloc_attempts_before_fail = -1;

			if( xml_tag != NULL )
			{
				libfplist_xml_tag_free(
				 &xml_tag,
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
			 "xml_tag",
			 xml_tag );

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
		/* Test libfplist_xml_tag_initialize with memset failing
		 */
		fplist_test_memset_attempts_before_fail = test_number;

		result = libfplist_xml_tag_initialize(
		          &xml_tag,
		          (uint8_t *) "data",
		          4,
		          &error );

		if( fplist_test_memset_attempts_before_fail != -1 )
		{
			fplist_test_memset_attempts_before_fail = -1;

			if( xml_tag != NULL )
			{
				libfplist_xml_tag_free(
				 &xml_tag,
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
			 "xml_tag",
			 xml_tag );

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
		/* Test libfplist_xml_tag_initialize with memcpy failing
		 */
		fplist_test_memcpy_attempts_before_fail = test_number;

		result = libfplist_xml_tag_initialize(
		          &xml_tag,
		          (uint8_t *) "data",
		          4,
		          &error );

		if( fplist_test_memcpy_attempts_before_fail != -1 )
		{
			fplist_test_memcpy_attempts_before_fail = -1;

			if( xml_tag != NULL )
			{
				libfplist_xml_tag_free(
				 &xml_tag,
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
			 "xml_tag",
			 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_free function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfplist_xml_tag_free(
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

/* Tests the libfplist_xml_tag_get_value_type function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_get_value_type(
     void )
{
	fplist_test_xml_tag_value_type_test_t tag_value_type_tests[ 10 ] = {
		{ LIBFPLIST_VALUE_TYPE_ARRAY,          "array",   5 },
		{ LIBFPLIST_VALUE_TYPE_BINARY_DATA,    "data",    4 },
		{ LIBFPLIST_VALUE_TYPE_BOOLEAN,        "false",   5 },
		{ LIBFPLIST_VALUE_TYPE_BOOLEAN,        "true",    4 },
		{ LIBFPLIST_VALUE_TYPE_DATE,           "date",    4 },
		{ LIBFPLIST_VALUE_TYPE_DICTIONARY,     "dict",    4 },
		{ LIBFPLIST_VALUE_TYPE_FLOATING_POINT, "real",    4 },
		{ LIBFPLIST_VALUE_TYPE_INTEGER,        "integer", 7 },
		{ LIBFPLIST_VALUE_TYPE_STRING,         "string",  6 },
		{ LIBFPLIST_VALUE_TYPE_UNKNOWN,        "unknown", 7 } };

	fplist_test_xml_tag_value_type_test_t *tag_value_type_test = NULL;
	libcerror_error_t *error                                   = NULL;
	libfplist_xml_tag_t *xml_tag                               = NULL;
	int result                                                 = 0;
	int test_number                                            = 0;
	int value_type                                             = 0;

	/* Test regular cases
	 */
	for( test_number = 0;
	     test_number < 10;
	     test_number++ )
	{
		tag_value_type_test = &( tag_value_type_tests[ test_number ] );

		result = libfplist_xml_tag_initialize(
		          &xml_tag,
		          (uint8_t *) tag_value_type_test->tag_name,
		          tag_value_type_test->tag_name_length,
		          &error );

		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FPLIST_TEST_ASSERT_IS_NOT_NULL(
		 "xml_tag",
		 xml_tag );

		FPLIST_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfplist_xml_tag_get_value_type(
		          xml_tag,
		          &value_type,
		          &error );

		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "value_type",
		 value_type,
		 tag_value_type_test->value_type );

		FPLIST_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfplist_xml_tag_free(
		          &xml_tag,
		          &error );

		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FPLIST_TEST_ASSERT_IS_NULL(
		 "xml_tag",
		 xml_tag );

		FPLIST_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_xml_tag_get_value_type(
	          NULL,
	          &value_type,
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

	result = libfplist_xml_tag_get_value_type(
	          xml_tag,
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
	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_compare_name function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_compare_name(
     void )
{
	libcerror_error_t *error     = NULL;
	libfplist_xml_tag_t *xml_tag = NULL;
	int result                   = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_xml_tag_compare_name(
	          xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_compare_name(
	          xml_tag,
	          (uint8_t *) "dict",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_xml_tag_compare_name(
	          NULL,
	          (uint8_t *) "data",
	          4,
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

	result = libfplist_xml_tag_compare_name(
	          xml_tag,
	          NULL,
	          4,
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

	result = libfplist_xml_tag_compare_name(
	          xml_tag,
	          (uint8_t *) "data",
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

	/* Clean up
	 */
	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_set_value function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_set_value(
     void )
{
	libcerror_error_t *error     = NULL;
	libfplist_xml_tag_t *xml_tag = NULL;
	int result                   = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_xml_tag_set_value(
	          xml_tag,
	          (uint8_t *) "value1",
	          6,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          xml_tag,
	          (uint8_t *) "value2",
	          6,
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
	result = libfplist_xml_tag_set_value(
	          NULL,
	          (uint8_t *) "value3",
	          6,
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

	result = libfplist_xml_tag_set_value(
	          xml_tag,
	          NULL,
	          6,
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

	result = libfplist_xml_tag_set_value(
	          xml_tag,
	          (uint8_t *) "value3",
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

#if defined( HAVE_FPLIST_TEST_MEMORY )

	/* Test libfplist_xml_tag_set_value with malloc failing
	 */
	fplist_test_malloc_attempts_before_fail = 0;

	result = libfplist_xml_tag_set_value(
	          xml_tag,
	          (uint8_t *) "value3",
	          6,
	          &error );

	if( fplist_test_malloc_attempts_before_fail != -1 )
	{
		fplist_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FPLIST_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( OPTIMIZATION_DISABLED )

	/* Test libfplist_xml_tag_set_value with memcpy failing
	 */
	fplist_test_memcpy_attempts_before_fail = 0;

	result = libfplist_xml_tag_set_value(
	          xml_tag,
	          (uint8_t *) "value3",
	          6,
	          &error );

	if( fplist_test_memcpy_attempts_before_fail != -1 )
	{
		fplist_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		FPLIST_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FPLIST_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_FPLIST_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_append_attribute function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_append_attribute(
     void )
{
	libcerror_error_t *error     = NULL;
	libfplist_xml_tag_t *xml_tag = NULL;
	int result                   = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_xml_tag_append_attribute(
	          xml_tag,
	          (uint8_t *) "name1",
	          5,
	          (uint8_t *) "value1",
	          6,
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
	result = libfplist_xml_tag_append_attribute(
	          NULL,
	          (uint8_t *) "name2",
	          5,
	          (uint8_t *) "value2",
	          6,
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

	result = libfplist_xml_tag_append_attribute(
	          xml_tag,
	          NULL,
	          5,
	          (uint8_t *) "value2",
	          6,
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

/* TODO test libcdata_array_append_entry failing */

	/* Clean up
	 */
	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_append_element function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_append_element(
     void )
{
	libcerror_error_t *error          = NULL;
	libfplist_xml_tag_t *element_tag1 = NULL;
	libfplist_xml_tag_t *element_tag2 = NULL;
	libfplist_xml_tag_t *xml_tag      = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "dict",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag1,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "element_tag1",
	 element_tag1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag2,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "element_tag2",
	 element_tag2 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_xml_tag_append_element(
	          xml_tag,
	          element_tag1,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	element_tag1 = NULL;

	/* Test error cases
	 */
	result = libfplist_xml_tag_append_element(
	          NULL,
	          element_tag2,
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

	result = libfplist_xml_tag_append_element(
	          xml_tag,
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

/* TODO test libcdata_array_append_entry failing */

	/* Clean up
	 */
	result = libfplist_xml_tag_free(
	          &element_tag2,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "element_tag2",
	 element_tag2 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( element_tag2 != NULL )
	{
		libfplist_xml_tag_free(
		 &element_tag2,
		 NULL );
	}
	if( element_tag1 != NULL )
	{
		libfplist_xml_tag_free(
		 &element_tag1,
		 NULL );
	}
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_get_number_of_elements function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_get_number_of_elements(
     void )
{
	libcerror_error_t *error          = NULL;
	libfplist_xml_tag_t *element_tag1 = NULL;
	libfplist_xml_tag_t *xml_tag      = NULL;
	int number_of_elements            = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "dict",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag1,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "element_tag1",
	 element_tag1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_append_element(
	          xml_tag,
	          element_tag1,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	element_tag1 = NULL;

	/* Test regular cases
	 */
	result = libfplist_xml_tag_get_number_of_elements(
	          xml_tag,
	          &number_of_elements,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "number_of_elements",
	 number_of_elements,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_xml_tag_get_number_of_elements(
	          NULL,
	          &number_of_elements,
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

	result = libfplist_xml_tag_get_number_of_elements(
	          xml_tag,
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
	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( element_tag1 != NULL )
	{
		libfplist_xml_tag_free(
		 &element_tag1,
		 NULL );
	}
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_xml_tag_get_element function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_xml_tag_get_element(
     void )
{
	libcerror_error_t *error          = NULL;
	libfplist_xml_tag_t *element_tag  = NULL;
	libfplist_xml_tag_t *element_tag1 = NULL;
	libfplist_xml_tag_t *xml_tag      = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &xml_tag,
	          (uint8_t *) "dict",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag1,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "element_tag1",
	 element_tag1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_append_element(
	          xml_tag,
	          element_tag1,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	element_tag1 = NULL;

	/* Test regular cases
	 */
	result = libfplist_xml_tag_get_element(
	          xml_tag,
	          0,
	          &element_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "element_tag",
	 element_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_xml_tag_get_element(
	          NULL,
	          0,
	          &element_tag,
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

	result = libfplist_xml_tag_get_element(
	          xml_tag,
	          -1,
	          &element_tag,
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
	result = libfplist_xml_tag_free(
	          &xml_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( element_tag1 != NULL )
	{
		libfplist_xml_tag_free(
		 &element_tag1,
		 NULL );
	}
	if( xml_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &xml_tag,
		 NULL );
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
	 "libfplist_xml_tag_initialize",
	 fplist_test_xml_tag_initialize );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_free",
	 fplist_test_xml_tag_free );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_get_value_type",
	 fplist_test_xml_tag_get_value_type );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_compare_name",
	 fplist_test_xml_tag_compare_name );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_set_value",
	 fplist_test_xml_tag_set_value );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_append_attribute",
	 fplist_test_xml_tag_append_attribute );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_append_element",
	 fplist_test_xml_tag_append_element );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_get_number_of_elements",
	 fplist_test_xml_tag_get_number_of_elements );

	FPLIST_TEST_RUN(
	 "libfplist_xml_tag_get_element",
	 fplist_test_xml_tag_get_element );

#endif /* defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


/*
 * Library property type test program
 *
 * Copyright (C) 2016-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fplist_test_libcerror.h"
#include "fplist_test_libfplist.h"
#include "fplist_test_macros.h"
#include "fplist_test_memory.h"
#include "fplist_test_unused.h"

#include "../libfplist/libfplist_property.h"
#include "../libfplist/libfplist_xml_tag.h"

#if defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT )

/* Tests the libfplist_property_initialize function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfplist_property_t *property  = NULL;
	libfplist_xml_tag_t *key_tag    = NULL;
	libfplist_xml_tag_t *value_tag  = NULL;
	int result                      = 0;

#if defined( HAVE_FPLIST_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_property_initialize(
	          NULL,
	          key_tag,
	          value_tag,
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

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	property = NULL;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
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

	/* Test invalid key tag
	 */
	result = libfplist_property_initialize(
	          &property,
	          value_tag,
	          key_tag,
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
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfplist_property_initialize with malloc failing
		 */
		fplist_test_malloc_attempts_before_fail = test_number;

		result = libfplist_property_initialize(
		          &property,
		          key_tag,
		          value_tag,
		          &error );

		if( fplist_test_malloc_attempts_before_fail != -1 )
		{
			fplist_test_malloc_attempts_before_fail = -1;

			if( property != NULL )
			{
				libfplist_property_free(
				 &property,
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
			 "property",
			 property );

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
		/* Test libfplist_property_initialize with memset failing
		 */
		fplist_test_memset_attempts_before_fail = test_number;

		result = libfplist_property_initialize(
		          &property,
		          key_tag,
		          value_tag,
		          &error );

		if( fplist_test_memset_attempts_before_fail != -1 )
		{
			fplist_test_memset_attempts_before_fail = -1;

			if( property != NULL )
			{
				libfplist_property_free(
				 &property,
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
			 "property",
			 property );

			FPLIST_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FPLIST_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfplist_xml_tag_free(
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT ) */

/* Tests the libfplist_property_free function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfplist_property_free(
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

#if defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT )

/* Tests the libfplist_property_get_value_type function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_value_type(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	int result                          = 0;
	int value_type                      = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_get_value_type(
	          property,
	          &value_type,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "value_type",
	 value_type,
	 LIBFPLIST_VALUE_TYPE_BINARY_DATA );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_property_get_value_type(
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_value_type(
	          property,
	          &value_type,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_value_type(
	          property,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_value_type(
	          property,
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

	/* Clean up
	 */
	result = libfplist_xml_tag_free(
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_value_data_size function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_value_data_size(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	size_t data_size                    = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "\nVEVTVA==\n",
	          10,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_get_value_data_size(
	          property,
	          &data_size,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_EQUAL_SIZE(
	 "data_size",
	 data_size,
	 (size_t) 4 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_property_get_value_data_size(
	          NULL,
	          &data_size,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_value_data_size(
	          property,
	          &data_size,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_value_data_size(
	          property,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_value_data_size(
	          property,
	          &data_size,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with missing value data
	 */
	result = libfplist_property_get_value_data_size(
	          property,
	          &data_size,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_value_data function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_value_data(
     void )
{
	uint8_t data[ 32 ];

	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "\nVEVTVA==\n",
	          10,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_get_value_data(
	          property,
	          data,
	          32,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          data,
	          "TEST",
	          4 );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libfplist_property_get_value_data(
	          NULL,
	          data,
	          32,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_value_data(
	          property,
	          data,
	          32,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_value_data(
	          property,
	          NULL,
	          32,
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

	result = libfplist_property_get_value_data(
	          property,
	          data,
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
	result = libfplist_xml_tag_free(
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_value_data(
	          property,
	          data,
	          32,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with missing value data
	 */
	result = libfplist_property_get_value_data(
	          property,
	          data,
	          32,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_value_integer function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_value_integer(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	uint64_t value_64bit                = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "integer",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "1234567890",
	          10,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_get_value_integer(
	          property,
	          &value_64bit,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_EQUAL_UINT64(
	 "value_64bit",
	 value_64bit,
	 (uint64_t) 1234567890 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "0xabcdef",
	          8,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_get_value_integer(
	          property,
	          &value_64bit,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_EQUAL_UINT64(
	 "value_64bit",
	 value_64bit,
	 (uint64_t) 0xabcdef );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_property_get_value_integer(
	          NULL,
	          &value_64bit,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_value_integer(
	          property,
	          &value_64bit,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_value_integer(
	          property,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_value_integer(
	          property,
	          &value_64bit,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "integer",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with missing value data
	 */
	result = libfplist_property_get_value_integer(
	          property,
	          &value_64bit,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_value_string function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_value_string(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	uint8_t *value_string               = NULL;
	size_t value_string_size            = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "string",
	          6,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "ABCDEFGHIJ",
	          10,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_get_value_string(
	          property,
	          &value_string,
	          &value_string_size,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_string",
	 value_string );

	FPLIST_TEST_ASSERT_EQUAL_SIZE(
	 "value_string_size",
	 value_string_size,
	 (size_t) 11 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          value_string,
	          "ABCDEFGHIJ",
	          11 );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

/* TODO change libfplist_property_get_value_string to be an internal function */
	memory_free(
	 value_string );

	value_string = NULL;

	/* Test error cases
	 */
	result = libfplist_property_get_value_string(
	          NULL,
	          &value_string,
	          &value_string_size,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_value_string(
	          property,
	          &value_string,
	          &value_string_size,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_value_string(
	          property,
	          NULL,
	          &value_string_size,
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

	result = libfplist_property_get_value_string(
	          property,
	          &value_string,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_value_string(
	          property,
	          &value_string,
	          &value_string_size,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "string",
	          6,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with missing value data
	 */
	result = libfplist_property_get_value_string(
	          property,
	          &value_string,
	          &value_string_size,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_value_uuid_string_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_value_uuid_string_copy_to_byte_stream(
     void )
{
	uint8_t expected_uuid_data[ 16 ] = {
		0xc3, 0x1c, 0x54, 0x34, 0x7b, 0xa4, 0x4f, 0xfa, 0xbd, 0x67, 0x99, 0xd9, 0x7a, 0x0a, 0xda, 0x0e };

	uint8_t uuid_data[ 16 ];

	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "string",
	          6,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "C31C5434-7BA4-4FFA-BD67-99D97A0ADA0E",
	          37,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
	          16,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          uuid_data,
	          expected_uuid_data,
	          16 );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          NULL,
	          uuid_data,
	          16,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
	          16,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          NULL,
	          16,
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

	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
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

#if defined( HAVE_FPLIST_TEST_MEMORY )

	/* Test libfplist_property_initialize with malloc failing in libfguid_identifier_copy_to_byte_stream
	 */
	fplist_test_malloc_attempts_before_fail = 2;

	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
	          16,
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

	/* Test libfplist_property_initialize with memcpy failing in libfguid_identifier_copy_to_byte_stream
	 */
	fplist_test_memcpy_attempts_before_fail = 2;

	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
	          16,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
	          16,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "string",
	          6,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_set_value(
	          value_tag,
	          (uint8_t *) "BOGUS",
	          5,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with invalid value data
	 */
	result = libfplist_property_value_uuid_string_copy_to_byte_stream(
	          property,
	          uuid_data,
	          16,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_array_number_of_entries function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_array_number_of_entries(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *element_tag    = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	int number_of_entries               = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "array",
	          5,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag,
	          (uint8_t *) "data",
	          4,
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

	result = libfplist_xml_tag_append_element(
	          value_tag,
	          element_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	element_tag = NULL;

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfplist_property_get_array_number_of_entries(
	          property,
	          &number_of_entries,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "number_of_entries",
	 number_of_entries,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfplist_property_get_array_number_of_entries(
	          NULL,
	          &number_of_entries,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_array_number_of_entries(
	          property,
	          &number_of_entries,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_array_number_of_entries(
	          property,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_array_number_of_entries(
	          property,
	          &number_of_entries,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( element_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &element_tag,
		 NULL );
	}
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_array_entry_by_index function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_array_entry_by_index(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *array_entry   = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_xml_tag_t *element_tag    = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "array",
	          5,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag,
	          (uint8_t *) "data",
	          4,
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

	result = libfplist_xml_tag_append_element(
	          value_tag,
	          element_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	element_tag = NULL;

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	array_entry = NULL;

	result = libfplist_property_get_array_entry_by_index(
	          property,
	          0,
	          &array_entry,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "array_entry",
	 array_entry );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfplist_property_free(
	          &array_entry,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "array_entry",
	 array_entry );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	array_entry = NULL;

	result = libfplist_property_get_array_entry_by_index(
	          NULL,
	          0,
	          &array_entry,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_array_entry_by_index(
	          property,
	          0,
	          &array_entry,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_array_entry_by_index(
	          property,
	          -1,
	          &array_entry,
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

	result = libfplist_property_get_array_entry_by_index(
	          property,
	          0,
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

	array_entry = (libfplist_property_t *) 0x12345678UL;

	result = libfplist_property_get_array_entry_by_index(
	          property,
	          0,
	          &array_entry,
	          &error );

	array_entry = NULL;

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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_array_entry_by_index(
	          property,
	          0,
	          &array_entry,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( element_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &element_tag,
		 NULL );
	}
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_property_get_sub_property_by_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_sub_property_by_utf8_name(
     void )
{
	libcerror_error_t *error            = NULL;
	libfplist_property_t *property      = NULL;
	libfplist_property_t *sub_property  = NULL;
	libfplist_xml_tag_t *element_tag1   = NULL;
	libfplist_xml_tag_t *element_tag2   = NULL;
	libfplist_xml_tag_t *key_tag        = NULL;
	libfplist_xml_tag_t *test_value_tag = NULL;
	libfplist_xml_tag_t *value_tag      = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "dict",
	          4,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &element_tag1,
	          (uint8_t *) "key",
	          3,
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

	result = libfplist_xml_tag_set_value(
	          element_tag1,
	          (uint8_t *) "MyKey",
	          5,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_append_element(
	          value_tag,
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

	result = libfplist_xml_tag_append_element(
	          value_tag,
	          element_tag2,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	element_tag2 = NULL;

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	sub_property = NULL;

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "MyKey",
	          5,
	          &sub_property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "sub_property",
	 sub_property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfplist_property_free(
	          &sub_property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "sub_property",
	 sub_property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	sub_property = NULL;

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "Bogus",
	          5,
	          &sub_property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "sub_property",
	 sub_property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfplist_property_free(
	          &sub_property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "sub_property",
	 sub_property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	sub_property = NULL;

	result = libfplist_property_get_sub_property_by_utf8_name(
	          NULL,
	          (uint8_t *) "MyKey",
	          5,
	          &sub_property,
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

	test_value_tag = ( (libfplist_internal_property_t *) property )->value_tag;

	( (libfplist_internal_property_t *) property )->value_tag = NULL;

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "MyKey",
	          5,
	          &sub_property,
	          &error );

	( (libfplist_internal_property_t *) property )->value_tag = test_value_tag;

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          NULL,
	          5,
	          &sub_property,
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

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "MyKey",
	          (size_t) SSIZE_MAX,
	          &sub_property,
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

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "MyKey",
	          5,
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

	sub_property = (libfplist_property_t *) 0x12345678UL;

	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "MyKey",
	          5,
	          &sub_property,
	          &error );

	sub_property = NULL;

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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfplist_xml_tag_initialize(
	          &key_tag,
	          (uint8_t *) "key",
	          3,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_initialize(
	          &value_tag,
	          (uint8_t *) "unknown",
	          7,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_initialize(
	          &property,
	          key_tag,
	          value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NOT_NULL(
	 "property",
	 property );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test with unsupported value type
	 */
	result = libfplist_property_get_sub_property_by_utf8_name(
	          property,
	          (uint8_t *) "MyKey",
	          5,
	          &sub_property,
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
	          &value_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "value_tag",
	 value_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_xml_tag_free(
	          &key_tag,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "key_tag",
	 key_tag );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfplist_property_free(
	          &property,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FPLIST_TEST_ASSERT_IS_NULL(
	 "property",
	 property );

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
	if( value_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &value_tag,
		 NULL );
	}
	if( key_tag != NULL )
	{
		libfplist_xml_tag_free(
		 &key_tag,
		 NULL );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
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
	 "libfplist_property_initialize",
	 fplist_test_property_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT ) */

	FPLIST_TEST_RUN(
	 "libfplist_property_free",
	 fplist_test_property_free );

#if defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT )

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_type",
	 fplist_test_property_get_value_type );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_data_size",
	 fplist_test_property_get_value_data_size );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_data",
	 fplist_test_property_get_value_data );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_integer",
	 fplist_test_property_get_value_integer );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_string",
	 fplist_test_property_get_value_string );

	FPLIST_TEST_RUN(
	 "libfplist_property_value_uuid_string_copy_to_byte_stream",
	 fplist_test_property_value_uuid_string_copy_to_byte_stream );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_array_number_of_entries",
	 fplist_test_property_get_array_number_of_entries );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_array_entry_by_index",
	 fplist_test_property_get_array_entry_by_index );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_sub_property_by_utf8_name",
	 fplist_test_property_get_sub_property_by_utf8_name );

#endif /* defined( __GNUC__ ) && !defined( LIBFPLIST_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


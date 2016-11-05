/*
 * Library property type testing program
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
#include "fplist_test_libcstring.h"
#include "fplist_test_libfplist.h"
#include "fplist_test_macros.h"
#include "fplist_test_memory.h"
#include "fplist_test_unused.h"

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

/* Tests the libfplist_property_get_value_type function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_property_get_value_type(
     void )
{
	libcerror_error_t *error       = NULL;
	libfplist_property_t *property = NULL;
	int result                     = 0;
	int value_type                 = 0;

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
	libcerror_error_t *error       = NULL;
	libfplist_property_t *property = NULL;
	size_t data_size               = 0;
	int result                     = 0;

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
	libcerror_error_t *error       = NULL;
	libfplist_property_t *property = NULL;
	uint64_t value_64bit           = 0;
	int result                     = 0;

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( property != NULL )
	{
		libfplist_property_free(
		 &property,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

	/* TODO add tests for libfplist_property_initialize */

	FPLIST_TEST_RUN(
	 "libfplist_property_free",
	 fplist_test_property_free );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_type",
	 fplist_test_property_get_value_type );

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_data_size",
	 fplist_test_property_get_value_data_size );

	/* TODO add tests for libfplist_property_get_value_data */

	FPLIST_TEST_RUN(
	 "libfplist_property_get_value_integer",
	 fplist_test_property_get_value_integer );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


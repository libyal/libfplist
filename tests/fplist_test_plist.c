/*
 * Library plist type testing program
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

/* Tests the libfplist_plist_initialize function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_plist_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libfplist_plist_t *plist      = NULL;
	int result               = 0;

	/* Test libfplist_plist_initialize
	 */
	result = libfplist_plist_initialize(
	          &plist,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NOT_NULL(
         "plist",
         plist );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfplist_plist_free(
	          &plist,
	          &error );

	FPLIST_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FPLIST_TEST_ASSERT_IS_NULL(
         "plist",
         plist );

        FPLIST_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfplist_plist_initialize(
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

	plist = (libfplist_plist_t *) 0x12345678UL;

	result = libfplist_plist_initialize(
	          &plist,
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

	plist = NULL;

#if defined( HAVE_FPLIST_TEST_MEMORY )

	/* Test libfplist_plist_initialize with malloc failing
	 */
	fplist_test_malloc_attempts_before_fail = 0;

	result = libfplist_plist_initialize(
	          &plist,
	          &error );

	if( fplist_test_malloc_attempts_before_fail != -1 )
	{
		fplist_test_malloc_attempts_before_fail = -1;

		if( plist != NULL )
		{
			libfplist_plist_free(
			 &plist,
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
		 "plist",
		 plist );

		FPLIST_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfplist_plist_initialize with memset failing
	 */
	fplist_test_memset_attempts_before_fail = 0;

	result = libfplist_plist_initialize(
	          &plist,
	          &error );

	if( fplist_test_memset_attempts_before_fail != -1 )
	{
		fplist_test_memset_attempts_before_fail = -1;

		if( plist != NULL )
		{
			libfplist_plist_free(
			 &plist,
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
		 "plist",
		 plist );

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
	if( plist != NULL )
	{
		libfplist_plist_free(
		 &plist,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfplist_plist_free function
 * Returns 1 if successful or 0 if not
 */
int fplist_test_plist_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfplist_plist_free(
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

	FPLIST_TEST_RUN(
	 "libfplist_plist_initialize",
	 fplist_test_plist_initialize );

	FPLIST_TEST_RUN(
	 "libfplist_plist_free",
	 fplist_test_plist_free );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


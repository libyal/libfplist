/*
 * Plist key functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfplist_definitions.h"
#include "libfplist_key.h"
#include "libfplist_libcerror.h"
#include "libfplist_types.h"

/* Creates a key
 * Make sure the value key is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfplist_key_initialize(
     libfplist_key_t **key,
     libcerror_error_t **error )
{
	libfplist_internal_key_t *internal_key = NULL;
	static char *function                  = "libfplist_key_initialize";

	if( key == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid key.",
		 function );

		return( -1 );
	}
	if( *key != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid key value already set.",
		 function );

		return( -1 );
	}
	internal_key = memory_allocate_structure(
	                libfplist_internal_key_t );

	if( internal_key == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create key.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_key,
	     0,
	     sizeof( libfplist_internal_key_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear key.",
		 function );

		goto on_error;
	}
	*key = (libfplist_key_t *) internal_key;

	return( 1 );

on_error:
	if( internal_key != NULL )
	{
		memory_free(
		 internal_key );
	}
	return( -1 );
}

/* Frees an key
 * Returns 1 if successful or -1 on error
 */
int libfplist_key_free(
     libfplist_key_t **key,
     libcerror_error_t **error )
{
	libfplist_internal_key_t *internal_key = NULL;
	static char *function                  = "libfplist_key_free";

	if( key == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid key.",
		 function );

		return( -1 );
	}
	if( *key != NULL )
	{
		internal_key = (libfplist_internal_key_t *) *key;
		*key         = NULL;

		memory_free(
		 internal_key );
	}
	return( 1 );
}


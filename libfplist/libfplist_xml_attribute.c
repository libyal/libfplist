/*
 * XML attribute functions
 *
 * Copyright (C) 2016-2025, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfplist_libcerror.h"
#include "libfplist_xml_attribute.h"

/* Creates an XML attribute
 * Make sure the value attribute is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_attribute_initialize(
     libfplist_xml_attribute_t **attribute,
     const uint8_t *name,
     size_t name_length,
     const uint8_t *value,
     size_t value_length,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_attribute_initialize";

	if( attribute == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML attribute.",
		 function );

		return( -1 );
	}
	if( *attribute != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid XML attribute value already set.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( ( name_length == 0 )
	 || ( name_length > (size_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name length value out of bounds.",
		 function );

		return( -1 );
	}
	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	if( ( value_length == 0 )
	 || ( value_length > (size_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value length value out of bounds.",
		 function );

		return( -1 );
	}
	*attribute = memory_allocate_structure(
	              libfplist_xml_attribute_t );

	if( *attribute == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create XML attribute.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *attribute,
	     0,
	     sizeof( libfplist_xml_attribute_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear XML attribute.",
		 function );

		memory_free(
		 *attribute );

		*attribute = NULL;

		return( -1 );
	}
	( *attribute )->name_size = name_length + 1;

	( *attribute )->name = (uint8_t *) memory_allocate(
	                                    sizeof( uint8_t ) * ( *attribute )->name_size );

	if( ( *attribute )->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     ( *attribute )->name,
	     name,
	     name_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		goto on_error;
	}
	( *attribute )->name[ name_length ] = 0;

	( *attribute )->value_size = value_length + 1;

	( *attribute )->value = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * ( *attribute )->value_size );

	if( ( *attribute )->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     ( *attribute )->value,
	     value,
	     value_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy value.",
		 function );

		goto on_error;
	}
	( *attribute )->value[ value_length ] = 0;

	return( 1 );

on_error:
	if( *attribute != NULL )
	{
		if( ( *attribute )->value != NULL )
		{
			memory_free(
			 ( *attribute )->value );
		}
		if( ( *attribute )->name != NULL )
		{
			memory_free(
			 ( *attribute )->name );
		}
		memory_free(
		 *attribute );

		*attribute = NULL;
	}
	return( -1 );
}

/* Frees an XML attribute
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_attribute_free(
     libfplist_xml_attribute_t **attribute,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_attribute_free";

	if( attribute == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML attribute.",
		 function );

		return( -1 );
	}
	if( *attribute != NULL )
	{
		if( ( *attribute )->value != NULL )
		{
			memory_free(
			 ( *attribute )->value );
		}
		if( ( *attribute )->name != NULL )
		{
			memory_free(
			 ( *attribute )->name );
		}
		memory_free(
		 *attribute );

		*attribute = NULL;
	}
	return( 1 );
}


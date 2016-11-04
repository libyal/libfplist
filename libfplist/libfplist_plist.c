/*
 * Plist functions
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
#include <memory.h>
#include <types.h>

#include "libfplist_key.h"
#include "libfplist_libcerror.h"
#include "libfplist_libcnotify.h"
#include "libfplist_plist.h"
#include "libfplist_types.h"
#include "libfplist_xml_parser.h"

extern \
int xml_parser_parse_buffer(
     libfplist_plist_t *plist,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error );

/* Creates a plist
 * Make sure the value plist is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfplist_plist_initialize(
    libfplist_plist_t **plist,
    libcerror_error_t **error )
{
	libfplist_internal_plist_t *internal_plist = NULL;
	static char *function                      = "libfplist_plist_initialize";

	if( plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid plist.",
		 function );

		return( -1 );
	}
	if( *plist != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid plist value already set.",
		 function );

		return( -1 );
	}
	internal_plist = memory_allocate_structure(
	                  libfplist_internal_plist_t );

	if( internal_plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create plist.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_plist,
	     0,
	     sizeof( libfplist_internal_plist_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear plist.",
		 function );
	
		memory_free(
		 internal_plist );

		return( -1 );
	}
	*plist = (libfplist_plist_t *) internal_plist;

	return( 1 );

on_error:
	if( internal_plist != NULL )
	{
		memory_free(
		 internal_plist );
	}
	return( -1 );
}

/* Frees a plist
 * Returns 1 if successful or -1 on error
 */
int libfplist_plist_free(
    libfplist_plist_t **plist,
    libcerror_error_t **error )
{
	libfplist_internal_plist_t *internal_plist = NULL;
	static char *function                      = "libfplist_plist_free";
	int result                                 = 1;

	if( plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid plist.",
		 function );

		return( -1 );
	}
	if( *plist != NULL )
	{
		internal_plist = (libfplist_internal_plist_t *) *plist;
		*plist         = NULL;

		/* The root_tag and dict_tag are referenced and freed elsewhere */

		if( libfplist_xml_tag_free(
		     &( internal_plist->root_tag ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free root XML tag.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_plist );
	}
	return( result );
}

/* Copies the plist from the byte stream
 * Returns 1 if successful, 0 if not a valid plist or -1 on error
 */
int libfplist_plist_copy_from_byte_stream(
     libfplist_plist_t *plist,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error )
{
	libfplist_internal_plist_t *internal_plist = NULL;
	uint8_t *buffer                            = NULL;
	static char *function                      = "libfplist_plist_copy_from_byte_stream";
	size_t buffer_size                         = 0;
	int result                                 = 0;

	if( plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid plist.",
		 function );

		return( -1 );
	}
	internal_plist = (libfplist_internal_plist_t *) plist;

	if( internal_plist->root_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid plist - root XML tag already set.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) INT_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid byte stream size value out of bounds.",
		 function );

		return( -1 );
	}
	/* Lex wants 2 zero bytes at the end of the buffer
	 */
	buffer_size = byte_stream_size + 1;

	buffer = (uint8_t *) memory_allocate(
	                      sizeof( uint8_t ) * buffer_size );

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create buffer.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     buffer,
	     byte_stream,
	     byte_stream_size - 1 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream.",
		 function );
	
		goto on_error;
	}
	/* Lex wants 2 zero bytes at the end of the buffer
	 */
	buffer[ buffer_size - 2 ] = 0;
	buffer[ buffer_size - 1 ] = 0;

	result = xml_parser_parse_buffer(
	          plist,
	          buffer,
	          buffer_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to parse XML.",
		 function );

		goto on_error;
	}
	memory_free(
	 buffer );

	buffer = NULL;

	return( 1 );

on_error:
	if( buffer != NULL )
	{
		memory_free(
		 buffer );
	}
	return( -1 );
}

/* Determines if the plist is an XML plist with a plist root element
 * Returns 1 if true, 0 if not or -1 on error
 */
int libfplist_plist_has_plist_root_element(
     libfplist_plist_t *plist,
     libcerror_error_t **error )
{
	libfplist_internal_plist_t *internal_plist = NULL;
	static char *function                      = "libfplist_plist_has_plist_root_element";

	if( plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid plist.",
		 function );

		return( -1 );
	}
	internal_plist = (libfplist_internal_plist_t *) plist;

	if( internal_plist->plist_tag == NULL )
	{
		return( 0 );
	}
	return( 1 );
}

/* Retrieves the root key
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfplist_plist_get_root_key(
     libfplist_plist_t *plist,
     libfplist_key_t **key,
     libcerror_error_t **error )
{
	libfplist_internal_plist_t *internal_plist = NULL;
	libfplist_xml_tag_t *element_tag           = NULL;
	static char *function                      = "libfplist_plist_get_root_key";
	int element_index                          = 0;
	int number_of_elements                     = 0;
	int result                                 = 0;

	if( plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid plist.",
		 function );

		return( -1 );
	}
	internal_plist = (libfplist_internal_plist_t *) plist;

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
	if( internal_plist->root_tag == NULL )
	{
		return( 0 );
	}
	if( internal_plist->dict_tag == NULL )
	{
		result = libfplist_xml_tag_compare_name(
		          internal_plist->root_tag,
		          (uint8_t *) "dict",
		          4,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of root tag.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			internal_plist->dict_tag = internal_plist->root_tag;
		}
	}
	if( internal_plist->dict_tag == NULL )
	{
		/* Ignore the plist XML node
		 * <plist version="1.0">
		 */
		result = libfplist_xml_tag_compare_name(
		          internal_plist->root_tag,
		          (uint8_t *) "plist",
		          5,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of root tag.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			internal_plist->plist_tag = internal_plist->root_tag;

			if( libfplist_xml_tag_get_number_of_elements(
			     internal_plist->root_tag,
			     &number_of_elements,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve number of elements.",
				 function );

				return( -1 );
			}
			for( element_index = 0;
			     element_index < number_of_elements;
			     element_index++ )
			{
				if( libfplist_xml_tag_get_element(
				     internal_plist->root_tag,
				     element_index,
				     &element_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				result = libfplist_xml_tag_compare_name(
				          element_tag,
				          (uint8_t *) "text",
				          4,
				          error );

				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to compare name of element tag: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				else if( result != 0 )
				{
					/* Ignore text nodes
					 */
					continue;
				}
				result = libfplist_xml_tag_compare_name(
				          element_tag,
				          (uint8_t *) "dict",
				          4,
				          error );

				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to compare name of element tag: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				else if( result != 0 )
				{
					internal_plist->dict_tag = element_tag;
				}
				else
				{
					break;
				}
			}
		}
	}
	if( internal_plist->dict_tag == NULL )
	{
		return( 0 );
	}
	if( libfplist_key_initialize(
	     key,
	     NULL,
	     internal_plist->dict_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create key.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the root tag
 * Returns 1 if successful or -1 on error
 */
int libfplist_plist_set_root_tag(
     libfplist_plist_t *plist,
     libfplist_xml_tag_t *tag,
     libcerror_error_t **error )
{
	libfplist_internal_plist_t *internal_plist = NULL;
	static char *function                      = "libfplist_plist_set_root_tag";

	if( plist == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid plist.",
		 function );

		return( -1 );
	}
	internal_plist = (libfplist_internal_plist_t *) plist;

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid tag.",
		 function );

		return( -1 );
	}
	internal_plist->root_tag = tag;

	return( 1 );
}


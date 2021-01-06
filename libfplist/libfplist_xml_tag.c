/*
 * XML tag functions
 *
 * Copyright (C) 2016-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <types.h>

#include "libfplist_definitions.h"
#include "libfplist_libcdata.h"
#include "libfplist_libcerror.h"
#include "libfplist_xml_attribute.h"
#include "libfplist_xml_tag.h"

/* Creates a XML plist tag
 * Make sure the value tag is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_initialize(
     libfplist_xml_tag_t **tag,
     const uint8_t *name,
     size_t name_length,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_initialize";

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( *tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid XML plist tag value already set.",
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
	*tag = memory_allocate_structure(
	        libfplist_xml_tag_t );

	if( *tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create XML plist tag.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *tag,
	     0,
	     sizeof( libfplist_xml_tag_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear XML plist tag.",
		 function );

		memory_free(
		 *tag );

		*tag = NULL;

		return( -1 );
	}
	( *tag )->name_size = name_length + 1;

	( *tag )->name = (uint8_t *) memory_allocate(
	                              sizeof( uint8_t ) * ( *tag )->name_size );

	if( ( *tag )->name == NULL )
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
	     ( *tag )->name,
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
	( *tag )->name[ name_length ] = 0;

	if( libcdata_array_initialize(
	     &( ( *tag )->attributes_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create attributes array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( ( *tag )->elements_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create elements array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *tag != NULL )
	{
		if( ( *tag )->attributes_array != NULL )
		{
			libcdata_array_free(
			 &( ( *tag )->attributes_array ),
			 NULL,
			 NULL );
		}
		if( ( *tag )->name != NULL )
		{
			memory_free(
			 ( *tag )->name );
		}
		memory_free(
		 *tag );

		*tag = NULL;
	}
	return( -1 );
}

/* Frees a XML plist tag
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_free(
     libfplist_xml_tag_t **tag,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_free";
	int result            = 1;

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( *tag != NULL )
	{
		/* The parent_tag is referenced and freed elsewhere */

		if( libcdata_array_free(
		     &( ( *tag )->elements_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfplist_xml_tag_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free elements array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *tag )->attributes_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfplist_xml_attribute_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free attributes array.",
			 function );

			result = -1;
		}
		if( ( *tag )->value != NULL )
		{
			memory_free(
			 ( *tag )->value );
		}
		if( ( *tag )->name != NULL )
		{
			memory_free(
			 ( *tag )->name );
		}
		memory_free(
		 *tag );

		*tag = NULL;
	}
	return( result );
}

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_get_value_type(
     libfplist_xml_tag_t *tag,
     int *value_type,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_get_value_type";

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( tag->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid tag - missing name.",
		 function );

		return( -1 );
	}
	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	*value_type = LIBFPLIST_VALUE_TYPE_UNKNOWN;

	if( tag->name_size == 5 )
	{
		if( narrow_string_compare(
		     tag->name,
		     "data",
		     4 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_BINARY_DATA;
		}
		else if( narrow_string_compare(
		          tag->name,
		          "date",
		          4 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_DATE;
		}
		else if( narrow_string_compare(
		          tag->name,
		          "dict",
		          4 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_DICTIONARY;
		}
		else if( narrow_string_compare(
		          tag->name,
		          "real",
		          4 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_FLOATING_POINT;
		}
		else if( narrow_string_compare(
		          tag->name,
		          "true",
		          4 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_BOOLEAN;
		}
	}
	else if( tag->name_size == 6 )
	{
		if( narrow_string_compare(
		     tag->name,
		     "array",
		     5 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_ARRAY;
		}
		else if( narrow_string_compare(
		          tag->name,
		          "false",
		          5 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_BOOLEAN;
		}
	}
	else if( tag->name_size == 7 )
	{
		if( narrow_string_compare(
		     tag->name,
		     "string",
		     6 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_STRING;
		}
	}
	else if( tag->name_size == 8 )
	{
		if( narrow_string_compare(
		     tag->name,
		     "integer",
		     7 ) == 0 )
		{
			*value_type = LIBFPLIST_VALUE_TYPE_INTEGER;
		}
	}
	return( 1 );
}

/* Compares the name
 * Returns 1 if equal, 0 if not or -1 on error
 */
int libfplist_xml_tag_compare_name(
     libfplist_xml_tag_t *tag,
     const uint8_t *name,
     size_t name_length,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_compare_name";

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
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
	if( name_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( tag->name_size != ( name_length + 1 ) )
	 || ( narrow_string_compare(
	       tag->name,
	       name,
	       name_length ) != 0 ) )
	{
		return( 0 );
	}
	return( 1 );
}

/* Sets the value
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_set_value(
     libfplist_xml_tag_t *tag,
     const uint8_t *value,
     size_t value_length,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_set_value";

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
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
	if( value_length > (size_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid value length value exceeds maximum allocation size.",
		 function );

		return( -1 );
	}
	if( tag->value != NULL )
	{
		memory_free(
		 tag->value );

		tag->value = NULL;
	}
	tag->value_size = value_length + 1;

	tag->value = (uint8_t *) memory_allocate(
	                          sizeof( uint8_t ) * tag->value_size );

	if( tag->value == NULL )
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
	     tag->value,
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
	tag->value[ value_length ] = 0;

	return( 1 );

on_error:
	if( tag->value != NULL )
	{
		memory_free(
		 tag->value );

		tag->value = NULL;
	}
	tag->value_size = 0;

	return( -1 );
}

/* Appends an attribute
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_append_attribute(
     libfplist_xml_tag_t *tag,
     const uint8_t *name,
     size_t name_length,
     const uint8_t *value,
     size_t value_length,
     libcerror_error_t **error )
{
	libfplist_xml_attribute_t *attribute = NULL;
	static char *function                = "libfplist_xml_tag_append_attribute";
	int entry_index                      = 0;

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( libfplist_xml_attribute_initialize(
	     &attribute,
	     name,
	     name_length,
	     value,
	     value_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create attribute.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     tag->attributes_array,
	     &entry_index,
	     (intptr_t *) attribute,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append attribute to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( attribute != NULL )
	{
		libfplist_xml_attribute_free(
		 &attribute,
		 NULL );
	}
	return( -1 );
}

int libfplist_xml_tag_append_element(
     libfplist_xml_tag_t *tag,
     libfplist_xml_tag_t *element_tag,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_append_element";
	int entry_index       = 0;

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( element_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist element tag.",
		 function );

		return( -1 );
	}
	if( libcdata_array_append_entry(
	     tag->elements_array,
	     &entry_index,
	     (intptr_t *) element_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append element tag to array.",
		 function );

		return( -1 );
	}
	element_tag->parent_tag = tag;

	return( 1 );
}

/* Retrieves the number of elements
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_get_number_of_elements(
     libfplist_xml_tag_t *tag,
     int *number_of_elements,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_get_number_of_elements";

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     tag->elements_array,
	     number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific element
 * Returns 1 if successful or -1 on error
 */
int libfplist_xml_tag_get_element(
     libfplist_xml_tag_t *tag,
     int element_index,
     libfplist_xml_tag_t **element_tag,
     libcerror_error_t **error )
{
	static char *function = "libfplist_xml_tag_get_element";

	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML plist tag.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     tag->elements_array,
	     element_index,
	     (intptr_t **) element_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	return( 1 );
}


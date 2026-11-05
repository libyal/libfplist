/*
 * OSS-Fuzz target for libfplist property type
 *
 * Copyright (C) 2016-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libfplist.h"

/* Limits on the traversal and buffer sizes to bound the time a single input takes
 */
#define FUZZER_ARRAY_ENTRY_LIMIT        8
#define FUZZER_DATA_SIZE_LIMIT          ( (size_t) 0x00100000 )
#define FUZZER_DICTIONARY_ENTRY_LIMIT   8
#define FUZZER_KEY_NAME_LENGTH_LIMIT    128
#define FUZZER_MAX_DEPTH                8
#define FUZZER_PROPERTY_LIMIT           64
#define FUZZER_LOOKUP_STRING_LIMIT      128

typedef struct fuzzer_key_name fuzzer_key_name_t;

struct fuzzer_key_name
{
	/* The name of a dictionary entry
	 */
	const uint8_t *name;

	/* The size of the name
	 */
	size_t name_length;

	/* The offset from which to start searching for the next name
	 */
	size_t next_offset;
};

/* Finds the next name within a <key>NAME</key> element of the fuzz data
 * The names are used as sub property lookup names
 * Returns 1 if successful or 0 when no more names are available
 */
int fuzzer_key_name_get(
     const uint8_t *data,
     size_t size,
     size_t offset,
     fuzzer_key_name_t *key_name )
{
	size_t index      = 0;
	size_t key_length = 0;
	size_t key_start  = 0;

	if( ( data == NULL )
	 || ( key_name == NULL ) )
	{
		return( 0 );
	}
	if( offset > size )
	{
		return( 0 );
	}
	index = offset;

	while( index + 5 <= size )
	{
		/* Search for the <key> element
		 */
		while( ( index + 5 <= size )
		 && ( ( data[ index ] != '<' )
		  ||  ( data[ index + 1 ] != 'k' )
		  ||  ( data[ index + 2 ] != 'e' )
		  ||  ( data[ index + 3 ] != 'y' )
		  ||  ( data[ index + 4 ] != '>' ) ) )
		{
			index += 1;
		}
		if( index + 5 > size )
		{
			return( 0 );
		}
		key_start = index + 5;

		/* Search for the </key> element
		 */
		index = key_start;

		while( index + 6 <= size )
		{
			if( ( data[ index ] == '<' )
			 && ( data[ index + 1 ] == '/' )
			 && ( data[ index + 2 ] == 'k' )
			 && ( data[ index + 3 ] == 'e' )
			 && ( data[ index + 4 ] == 'y' )
			 && ( data[ index + 5 ] == '>' ) )
			{
				break;
			}
			index += 1;
		}
		if( index + 6 > size )
		{
			return( 0 );
		}
		key_length = index - key_start;

		if( ( key_length > 0 )
		 && ( key_length <= FUZZER_KEY_NAME_LENGTH_LIMIT ) )
		{
			key_name->name         = &( data[ key_start ] );
			key_name->name_length  = key_length;
			key_name->next_offset  = index + 6;

			return( 1 );
		}
		index = key_start;
	}
	return( 0 );
}

/* Decodes a property and its sub properties, array entries and values
 * using the typed accessors
 * Returns 1 if successful or -1 on error
 */
int property_decode_fuzzer(
    const uint8_t *data,
    size_t size,
    int depth,
    libfplist_property_t *property,
    int *property_count )
{
	fuzzer_key_name_t fuzzer_key_name;
	uint8_t uuid_byte_stream[ 32 ];

	libfplist_property_t *array_entry  = NULL;
	libfplist_property_t *sub_property = NULL;
	uint8_t *value_data                = NULL;
	uint8_t *value_string              = NULL;
	size_t data_size                   = 0;
	size_t next_offset                 = 0;
	size_t lookup_string_length        = 0;
	size_t string_size                 = 0;
	uint64_t value_64bit               = 0;
	uint8_t value_byte                 = 0;
	int number_of_entries              = 0;
	int entry_index                    = 0;
	int entries_limit                  = 0;
	int number_of_key_names            = 0;
	int value_type                     = 0;

	if( ( data == NULL )
	 || ( property == NULL )
	 || ( property_count == NULL ) )
	{
		return( -1 );
	}
	if( ( depth > FUZZER_MAX_DEPTH )
	 || ( *property_count >= FUZZER_PROPERTY_LIMIT ) )
	{
		return( 0 );
	}
	*property_count += 1;

	if( libfplist_property_get_value_type(
	     property,
	     &value_type,
	     NULL ) != 1 )
	{
		return( -1 );
	}
	value_byte ^= (uint8_t) value_type;

	libfplist_property_get_value_data_size(
	 property,
	 NULL,
	 NULL );

	/* Retrieves the value (binary) data
	 */
	if( libfplist_property_get_value_data_size(
	     property,
	     &data_size,
	     NULL ) == 1 )
	{
		if( ( data_size > 0 )
		 && ( data_size <= FUZZER_DATA_SIZE_LIMIT ) )
		{
			value_data = (uint8_t *) malloc( data_size );

			if( value_data != NULL )
			{
				libfplist_property_get_value_data(
				 property,
				 NULL,
				 (size_t) 32,
				 NULL );

				if( libfplist_property_get_value_data(
				     property,
				     value_data,
				     data_size,
				     NULL ) == 1 )
				{
					value_byte ^= value_data[ 0 ];
				}
				free(
				 value_data );

				value_data = NULL;
			}
		}
	}
	/* Retrieves an integer value
	 */
	if( libfplist_property_get_value_integer(
	     property,
	     &value_64bit,
	     NULL ) == 1 )
	{
		value_byte ^= (uint8_t) value_64bit;
	}
	/* Retrieves a string value
	 */
	libfplist_property_get_value_string(
	 property,
	 NULL,
	 &string_size,
	 NULL );

	libfplist_property_get_value_string(
	 property,
	 &value_string,
	 NULL,
	 NULL );

	if( libfplist_property_get_value_string(
	     property,
	     &value_string,
	     &string_size,
	     NULL ) == 1 )
	{
		if( string_size > 0 )
		{
			value_byte ^= value_string[ 0 ];
		}
		free(
		 value_string );

		value_string = NULL;
	}
	/* Retrieves a UUID (GUID) string value
	 */
	libfplist_property_value_uuid_string_copy_to_byte_stream(
	 property,
	 uuid_byte_stream,
	 sizeof( uuid_byte_stream ),
	 NULL );

	/* Retrieves the number of array entries
	 */
	libfplist_property_get_array_number_of_entries(
	 property,
	 NULL,
	 NULL );

	if( libfplist_property_get_array_number_of_entries(
	     property,
	     &number_of_entries,
	     NULL ) == 1 )
	{
		if( number_of_entries > 0 )
		{
			entries_limit = number_of_entries;

			if( entries_limit > FUZZER_ARRAY_ENTRY_LIMIT )
			{
				entries_limit = FUZZER_ARRAY_ENTRY_LIMIT;
			}
			for( entry_index = 0; entry_index < entries_limit; entry_index++ )
			{
				if( libfplist_property_get_array_entry_by_index(
				     property,
				     entry_index,
				     &array_entry,
				     NULL ) == 1 )
				{
					value_byte ^= (uint8_t) property_decode_fuzzer(
					                         data,
					                         size,
					                         depth + 1,
					                         array_entry,
					                         property_count );

					libfplist_property_free(
					 &array_entry,
					 NULL );
				}
				array_entry = NULL;
			}
			if( libfplist_property_get_array_entry_by_index(
			     property,
			     number_of_entries,
			     &array_entry,
			     NULL ) == 1 )
			{
				libfplist_property_free(
				 &array_entry,
				 NULL );
			}
			array_entry = NULL;
		}
		else
		{
			if( libfplist_property_get_array_entry_by_index(
			     property,
			     0,
			     &array_entry,
			     NULL ) == 1 )
			{
				libfplist_property_free(
				 &array_entry,
				 NULL );
			}
			array_entry = NULL;
		}
	}
	else
	{
		if( libfplist_property_get_array_entry_by_index(
		     property,
		     0,
		     &array_entry,
		     NULL ) == 1 )
		{
			libfplist_property_free(
			 &array_entry,
			 NULL );
		}
		array_entry = NULL;
	}
	libfplist_property_get_sub_property_by_utf8_name(
	 property,
	 NULL,
	 0,
	 &sub_property,
	 NULL );

	sub_property = NULL;

	libfplist_property_get_sub_property_by_utf8_name(
	 property,
	 (uint8_t *) "name",
	 4,
	 NULL,
	 NULL );

	/* Retrieves the sub property for the specific UTF-8 encoded name.
	 * Uses the <key>NAME</key> names found in the fuzz data such that
	 * both the found and not found branches are exercised
	 */
	next_offset = 0;

	while( ( number_of_key_names < FUZZER_DICTIONARY_ENTRY_LIMIT )
	       && ( fuzzer_key_name_get(
	               data,
	               size,
	               next_offset,
	               &fuzzer_key_name ) == 1 ) )
	{
		if( libfplist_property_get_sub_property_by_utf8_name(
		     property,
		     fuzzer_key_name.name,
		     fuzzer_key_name.name_length,
		     &sub_property,
		     NULL ) == 1 )
		{
			value_byte ^= (uint8_t) property_decode_fuzzer(
			                         data,
			                         size,
			                         depth + 1,
			                         sub_property,
			                         property_count );

			libfplist_property_free(
			 &sub_property,
			 NULL );
		}
		sub_property = NULL;
		next_offset  = fuzzer_key_name.next_offset;

		number_of_key_names += 1;
	}
	/* Also uses a lookup name derived from the fuzz data.
	 * The data is not necessarily a valid UTF-8 string
	 * which exercises the validation branches in the library
	 */
	if( size > 0 )
	{
		lookup_string_length = size;

		if( lookup_string_length > FUZZER_LOOKUP_STRING_LIMIT )
		{
			lookup_string_length = FUZZER_LOOKUP_STRING_LIMIT;
		}
		if( libfplist_property_get_sub_property_by_utf8_name(
		     property,
		     data,
		     lookup_string_length,
		     &sub_property,
		     NULL ) == 1 )
		{
			value_byte ^= (uint8_t) property_decode_fuzzer(
			                         data,
			                         size,
			                         depth + 1,
			                         sub_property,
			                         property_count );

			libfplist_property_free(
			 &sub_property,
			 NULL );
		}
		sub_property = NULL;
	}
	/* Use the decoded values as a sink to keep them live
	 */
	if( value_byte == 0 )
	{
		/* No action required
		 */
	}
	return( 1 );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libfplist_property_t *root_property      = NULL;
	libfplist_property_list_t *property_list = NULL;
	int property_count                       = 0;

	if( libfplist_property_list_initialize(
	     &property_list,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libfplist_property_list_copy_from_byte_stream(
	     property_list,
	     data,
	     size,
	     NULL ) == 1 )
	{
		libfplist_property_list_has_plist_root_element(
		 NULL,
		 NULL );

		libfplist_property_list_has_plist_root_element(
		 property_list,
		 NULL );

		libfplist_property_list_get_root_property(
		 property_list,
		 NULL,
		 NULL );

		if( libfplist_property_list_get_root_property(
		     property_list,
		     &root_property,
		     NULL ) == 1 )
		{
			libfplist_property_list_get_root_property(
			 property_list,
			 &root_property,
			 NULL );

			/* Decodes the property and its sub properties,
			 * array entries and values using the typed accessors
			 */
			property_decode_fuzzer(
			 data,
			 size,
			 0,
			 root_property,
			 &property_count );

			libfplist_property_free(
			 &root_property,
			 NULL );
		}
	}
	libfplist_property_list_free(
	 &property_list,
	 NULL );

	return( 0 );
}

} /* extern "C" */

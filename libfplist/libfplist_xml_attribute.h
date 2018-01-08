/*
 * XML attribute functions
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

#if !defined( _LIBFPLIST_XML_ATTRIBUTE_H )
#define _LIBFPLIST_XML_ATTRIBUTE_H

#include <common.h>
#include <types.h>

#include "libfplist_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfplist_xml_attribute libfplist_xml_attribute_t;

struct libfplist_xml_attribute
{
	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	size_t name_size;

	/* The value (value)
	 */
	uint8_t *value;

	/* The value size
	 */
	size_t value_size;
};

int libfplist_xml_attribute_initialize(
     libfplist_xml_attribute_t **attribute,
     const uint8_t *name,
     size_t name_length,
     const uint8_t *value,
     size_t value_length,
     libcerror_error_t **error );

int libfplist_xml_attribute_free(
     libfplist_xml_attribute_t **attribute,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFPLIST_XML_ATTRIBUTE_H ) */


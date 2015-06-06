/*
 *  Copyright (c) 2015 Ryan McCullagh <me@ryanmccullagh.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __SMART_STRING_H__
#define __SMART_STRING_H__

#include <stddef.h>
#include <stdbool.h>

#define FORMAT_ATTR(x, y) __attribute__ ((format (printf, x, y)))

typedef struct SmartString {
	size_t length;
	size_t capacity;
	char* buffer;
} SmartString;

SmartString* smart_string_new(void);
bool smart_string_append(SmartString* ss, const char* str);
bool FORMAT_ATTR(2, 3) smart_string_append_sprintf(SmartString* ss, const char* format, ...);
void smart_string_destroy(SmartString* ss);
bool smart_string_starts_with(SmartString* ss, const char* str);
bool smart_string_ends_with(SmartString* ss, const char* str);

#endif /* __SMART_STRING_H__ */

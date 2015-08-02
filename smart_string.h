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

#define SMART_STRING_FUNC(name, ...) \
	smart_string_##name(SmartString* ss, __VA_ARGS__)

#if defined _WIN32
	#define FORMAT_ATTR(x, y)
#else
	#define FORMAT_ATTR(x, y) __attribute__ ((format (printf, x, y)))
#endif

typedef struct SmartString {
	size_t length;
	size_t capacity;
	char* buffer;
} SmartString;


#if defined _WIN32
	#define SMART_STRING_PUBLIC __declspec(dllexport)
#else
	#define SMART_STRING_PUBLIC __attribute__ ((visibility("default")))
#endif

#define SMART_STRING_API SMART_STRING_PUBLIC

#ifdef __cplusplus
extern "C" {
#endif
	extern SMART_STRING_API SmartString* smart_string_new(void);
	extern SMART_STRING_API bool smart_string_append(SmartString* ss, const char* str);
	extern SMART_STRING_API bool FORMAT_ATTR(2, 3) smart_string_append_sprintf(SmartString* ss, const char* format, ...);
	extern SMART_STRING_API void smart_string_destroy(SmartString* ss);
	extern SMART_STRING_API bool smart_string_starts_with(SmartString* ss, const char* str);
	extern SMART_STRING_API bool smart_string_ends_with(SmartString* ss, const char* str);
#ifdef __cplusplus
}
#endif

#endif /* __SMART_STRING_H__ */

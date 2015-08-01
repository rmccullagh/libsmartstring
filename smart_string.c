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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "smart_string.h"

#define D_SMART_STRING_SIZE 16

#ifdef __cplusplus
extern "C" {
#endif

SMART_STRING_API SmartString* smart_string_new(void)
{

	SmartString* ss;
	if ((ss = (SmartString* )malloc(sizeof(SmartString))) == NULL) {
		return NULL;
	}
	ss->length = 0;
	ss->capacity = D_SMART_STRING_SIZE;
	if ((ss->buffer = (char *)malloc(ss->capacity)) == NULL) {
		free(ss);
		return NULL;
	}
	ss->buffer[ss->length] = '\0';
	return ss;
}

SMART_STRING_API
bool SMART_STRING_FUNC(append, const char* str)
{
	if (ss == NULL) { return false; }
	if (str == NULL) { return false; }

	size_t part_length = strlen(str);
	size_t i;
	size_t current_position;
	size_t new_length;

	if (part_length == 0) {
		return true;
	}

	new_length = part_length + ss->length;
	current_position = ss->length;

	if (new_length >= ss->capacity) {
		while (new_length >= ss->capacity) {
			ss->capacity *= 2;
			if ((ss->buffer = (char *)realloc(ss->buffer, ss->capacity)) == NULL) {
				return false;
			}
		}
	}

	for (i = 0; i < part_length; i++) {
		ss->buffer[current_position++] = str[i];
	}

	ss->length = new_length;
	ss->buffer[current_position] = '\0';

	return true;
}

SMART_STRING_API
bool FORMAT_ATTR(2, 3) SMART_STRING_FUNC(append_sprintf, const char* format, ...)
{
	if ((ss == NULL) || (format == NULL)) { return false; }
	if (strlen(format) == 0) {
		return true;
	}

	va_list args;
	int buffer_size = D_SMART_STRING_SIZE;
	char* buffer, *buffer2;
	int n;
	if ((buffer = (char *)malloc(buffer_size)) == NULL) {
		return false;
	}

	for (;;) {
		va_start(args, format);
		#ifdef _WIN32
				n = vsprintf_s(buffer, buffer_size, format, args);
		#else
				n = vsnprintf(buffer, buffer_size, format, args);
		#endif
		va_end(args);

		if (n < 0) {
			free(buffer);
			return false;
		}

		if (n < buffer_size) {
			smart_string_append(ss, buffer);
			free(buffer);
			return true;
		}

		buffer_size = buffer_size + 1;

		if ((buffer2 = (char *)realloc(buffer, buffer_size)) == NULL) {
			free(buffer);
			return false;
		}
		else {
			buffer = buffer2;
		}
	}

	return false;

}

SMART_STRING_API
void smart_string_destroy(SmartString* ss)
{
	if (ss == NULL) {
		return;
	}
	#ifdef DEBUG
	printf("%s(): destroying SmartString instance : \n", __func__);
	printf("SmartString {\n");
	printf("\tlength   = %zu\n", ss->length);
	printf("\tcapacity = %zu\n", ss->capacity);
	if (ss->buffer != NULL) {
		printf("\tbuffer   = \"%s\"\n", ss->buffer);
	}
	printf("}\n");
	#endif
	if (ss->buffer != NULL) {
		free(ss->buffer);
	}

	free(ss);
}

SMART_STRING_API
bool SMART_STRING_FUNC(starts_with, const char* str)
{
	if ((ss == NULL) || (str == NULL)) { return false; }
	size_t part_length = strlen(str);
	size_t i;
	if (part_length == 0) {
		return false;
	}
	if (part_length > ss->length) {
		return false;
	}
	for (i = 0; i < part_length; i++) {
		if (ss->buffer[i] != str[i]) {
			return false;
		}
	}

	return true;
}

SMART_STRING_API
bool SMART_STRING_FUNC(ends_with, const char* str)
{
	if ((ss == NULL) || (str == NULL)) { return false; }
	int part_length = strlen(str);
	int i;
	if (part_length == 0) {
		return false;
	}
	if ((unsigned int)part_length > ss->length) {
		return false;
	}
	size_t end = ss->length - 1;
	for (i = (part_length - 1); i >= 0; i--) {
		if (ss->buffer[end--] != str[i]) {
			return false;
		}
	}

	return true;
}

#ifdef __cplusplus
}
#endif


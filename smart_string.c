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

SmartString* smart_string_new(void)
{
	SmartString* ss;
	if((ss = malloc(sizeof(SmartString))) == NULL) {
		return NULL;
	}
	ss->length = 0;
	ss->capacity = D_SMART_STRING_SIZE;
	if((ss->buffer = malloc(ss->capacity)) == NULL) {
		free(ss);
		return NULL;
	}
	ss->buffer[ss->length] = '\0';
	return ss;
}

bool smart_string_append(SmartString* ss, const char* str)
{
	if(ss == NULL) { return false; }
	if(str == NULL) { return false; }
	
	size_t part_length = strlen(str);
	size_t i;
	size_t current_position;
	size_t new_length;
	
	if(part_length == 0) {
		return true;
	}
	
	new_length = part_length + ss->length;
	current_position = ss->length;
	
	if(new_length >= ss->capacity) {
		while(new_length >= ss->capacity) {
			ss->capacity *= 2;
			if((ss->buffer = realloc(ss->buffer, ss->capacity)) == NULL) {
				return false;
			} 
		}
	}
	
	for(i = 0; i < part_length; i++) {
		ss->buffer[current_position++] = str[i];
	}
	
	ss->length = new_length;
	ss->buffer[current_position] = '\0';
	
	return true;
}

bool FORMAT_ATTR(2, 3) smart_string_append_sprintf(SmartString* ss, const char* format, ...)
{
	if((ss == NULL) || (format == NULL)) {
		return false;
	}

	if(strlen(format) == 0) {
		return true;
	}

	va_list args;
        int buffer_size = D_SMART_STRING_SIZE;
        char* buffer, *buffer2;
        int n;
        if((buffer = malloc(buffer_size)) == NULL) {
                return false;
        }

        for(;;) {
                va_start(args, format);
                n = vsnprintf(buffer, buffer_size, format, args);
                va_end(args);

                if(n < 0) {
                        free(buffer);
                        return false;
                }

                if(n < buffer_size) {
                        smart_string_append(ss, buffer);
			free(buffer);
                        return true;
                }

                buffer_size = buffer_size + 1;

                if((buffer2 = realloc(buffer, buffer_size)) == NULL) {
                        free(buffer);
                        return false;
                } else {
                        buffer = buffer2;
                }
        }

        return false;

}

void smart_string_destroy(SmartString* ss)
{
	#ifdef DEBUG
		printf("debug:%s destroying SmartString instance: \n", __func__);
		printf("SmartString {\n");
		printf("\tlength   = %zu\n",  ss->length);
		printf("\tcapacity = %zu\n",  ss->capacity);
		printf("\tbuffer   = \"%s\"\n", ss->buffer);
		printf("}\n");
	#endif
	free(ss->buffer);
	free(ss);
}

bool smart_string_starts_with(SmartString* ss, const char* str)
{
		if((ss == NULL) || (str == NULL)) { return false; }
		size_t part_length = strlen(str);
		size_t i;
		if(part_length == 0) {
			return false;
		}
		if(part_length > ss->length) {
			return false;
		}
		for(i = 0; i < part_length; i++) {
			if(ss->buffer[i] != str[i]) {
				return false;
			}
		}

		return true;
}

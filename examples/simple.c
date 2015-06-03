#include <stdio.h>
#include "../smart_string.h"

int main()
{
	SmartString* ss = smart_string_new();
	if(!ss) {
		return 1;
	}
	
	smart_string_append(ss, "http://");
	smart_string_append(ss, "www.google.com");
	smart_string_append(ss, "?");
	smart_string_append(ss, "tracking=1");
	smart_string_append(ss, "&");
	smart_string_append(ss, "browser=chrome");
	smart_string_append(ss, "&sk=true");
	
	if(!smart_string_starts_with(ss, "https")) {
		printf("only accepting https\n"); 
	} else {
		printf("%s\n", ss->buffer);
	}
	
	printf("%s\n", ss->buffer);
	smart_string_destroy(ss);

	SmartString* str = smart_string_new();
    	smart_string_append(str, "a long string with more than 32 characters.");
	printf("%s\n", str->buffer);
	smart_string_destroy(str);


	return 0;
}

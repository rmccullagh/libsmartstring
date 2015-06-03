#include <stdio.h>
#include "../smart_string.h"
int main()
{
	SmartString* ss = smart_string_new();
	if(!ss) return 1;

	if(!smart_string_append(ss, "This is a test")) {
		printf("smart_string_append failed\n");
		smart_string_destroy(ss);
		return 1;
	}
	
	
	printf("%s\n", ss->buffer);

	smart_string_destroy(ss);

	return 0;
}

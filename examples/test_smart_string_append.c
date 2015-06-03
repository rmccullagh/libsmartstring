#include <stdio.h>
#include <assert.h>
#include "../smart_string.h"
int main()
{
	SmartString* ss = smart_string_new();
	if(!ss) return 1;

	int status = smart_string_append(ss, NULL);

	assert(status == 0);	
	
	printf("%s\n", ss->buffer);

	smart_string_destroy(ss);

	return 0;
}

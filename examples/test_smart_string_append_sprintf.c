#include <stdio.h>
#include "../smart_string.h"

int main()
{
	SmartString* ss = smart_string_new();
	if(!ss) return 1;

	if(!smart_string_append_sprintf(ss, "%s:%s:%d", __FILE__, __FUNCTION__,__LINE__)) {
		printf("debug: smartt_string_append_sprintf failed\n");
		smart_string_destroy(ss);
		return 1;	
	}

	printf("%s\n", ss->buffer);

	smart_string_destroy(ss);
	return 0;
}

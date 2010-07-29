#include <stdio.h>
#include <stdarg.h>

void second(const int count, ...){
	va_list list;
	va_start(list, count);
	
	int i;
	for (i=0; i<count; ++i) {
		char *to_print;
		to_print = va_arg(list, char *);
		printf("%d: %s\n", i+1, to_print );
	}
	va_end(list);
}

int main (void)
{
	second(8,"ein","2","three","ctyri!","piat","VI","seti", "vosum pyco");
	return 0;
}


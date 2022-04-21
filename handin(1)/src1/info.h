#include <stdio.h>


#define INFO(fmt, args...)	\
	(fprintf(fp_info, fmt, ## args),	\
	 fprintf(fp_info, "\n"))

extern FILE *fp_info;

extern char *comma(unsigned long long x, char *buf, unsigned int length);

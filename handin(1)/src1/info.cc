#include <stdio.h>
#include <monetary.h>
#include <locale.h>

FILE *fp_info;

char *comma(unsigned long long x, char *buf, unsigned int length) {
	// set locale to U.S.
	setlocale(LC_ALL, "en_US");

	strfmon(buf, length, "%!.0n", (double)x);

	return(buf);
}

#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

char* progname;

void error(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);

	if (progname != NULL)
		fprintf(stderr, "%s: ", progname);

	vfprintf(stderr, fmt, ap);
	
	if (errno != 0)
		fprintf(stderr, ": %s", strerror(errno));

	fputc('\n', stderr);

	va_end(ap);

	exit(1);
}

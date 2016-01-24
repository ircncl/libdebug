#include <debug.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main ()
{
	LIBDEBUG = 1; /* required for debug() lines to do anything */

	errno = 0;
	pline(1, "/etc/passwd");
	if(errno)
		perror("pline");

	errno = 0;
	debug(-20, "Out of range\n");
	if(errno)
		perror("pline");

	errno = 0;
	debug(-4, "In range!\n");
	if(errno)
		perror("pline");

	return errno;
	return errno;
}

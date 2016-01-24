#include <debug.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int LIBDEBUG = 1; /* required for debug() lines to do anything */

int main(void)
{
	int local_errno;

	errno = 0;
	pline(1, "/etc/passwd");
	local_errno = errno;

	debug(-3, "pline returned %d\n", local_errno);

	LIBDEBUG = 0; /* Disable libdebug */

	debug(0, "This line now does nothing\n","");
	/* ,"" required by C99 but most compilers don't need it */

	return errno;
}

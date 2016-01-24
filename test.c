#include "debug.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
	int local_errno;

	errno = 0;
	pline(1, "/etc/passwd");
	local_errno = errno;

	debug(-3, "pline returned %d\n", local_errno);

	return errno;
}

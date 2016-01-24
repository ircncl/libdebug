#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "debug.h"

/* open/read/closing a file per each call is fast enough for now, but in the
 * future, should we support keeping files open in memory? Is the overhead of
 * that worth it? I really want to keep this a simple function.
 */

/*
 * pline; print line from file
 * eg: pline("/etc/motd", 3); //print line 3 of /etc/motd
 */
int pline (const int line, const char *path)
{
	int c; /* char */
	int n; /* newline count */
	size_t len;
	char *s;
	FILE *fd;

	n = 1;
	s = NULL;
	fd = fopen(path, "r");

	if (!fd)
		return errno;

	while (line > n && (c = fgetc(fd)) != EOF)
		if(c == '\n')
			n++;

	if (line != n) { /* fgetc error */
		if(!errno) {
			return (errno = ESPIPE); /* Is this the right error? */
		} else {
			return errno;
		}
	}
	if (getline(&s, &len, fd) == -1)
		return errno;
	if (fprintf(stderr, "%d. %s", line, s) < 0)
		return errno;
	if (fclose(fd) != 0)
		return errno;

	return 0;
}

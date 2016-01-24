#pragma once
#ifndef LIB_DEBUG_H
#define LIB_DEBUG_H
/* ^ No reason not to use both right? */

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

int pline (const int line, const char *path);
int LIBDEBUG;

static inline int libdebug_wrapper (const int line, const char *path,
                                    const char *func, const char *fmt, ...)
{
	va_list varg;
	va_start(varg, fmt);

	if (LIBDEBUG) {
		fprintf(stderr, "\n\r\033[00;37m@%s:%d in %s():\n", path, line,
		                func);
		if(errno)
			return errno;
		pline(line, path);
		if(errno)
			return errno;
		vfprintf(stderr, fmt, varg);
		if(errno)
			return errno;
		fprintf(stderr, "\033[00;00m");
		if(errno)
			return errno;
	}
	va_end(varg);
	return 0;
}

#define debug(l, s, ...) \
	libdebug_wrapper(__LINE__+l, __FILE__, __func__, s, ##__VA_ARGS__);\

#endif

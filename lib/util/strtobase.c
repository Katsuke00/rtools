#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <stdlib.h>

#include "util.h"

ssize_t
strtobase(const char *str, ssize_t min, ssize_t max, int base)
{
	ssize_t res;
	char *end;

	errno = 0;
	res   = strtoll(str, &end, base);

	if (end == str || *end != '\0')
		errno = EINVAL;

	if (res > max || res < min)
		errno = ERANGE;

	if (errno)
		err(1, "strtobase %s", str);

	return res;
}


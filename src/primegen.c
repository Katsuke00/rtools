#include <sys/types.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define COLUMNS 80
#define SAFEZON 8

static int
numlen(ssize_t num) {
	ssize_t res;

	for (res = 0; num; res++)
		num /= 10;

	return res;
}

static void
usage(void)
{
	fprintf(stderr, "usage: %s from to\n", getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	ssize_t i, from, to;
	int chrp, ndiv;

	setprogname(argv[0]);
	argc--, argv++;

	if (argc < 2)
		usage();

	from = strtobase(argv[0], 1, SSIZE_MAX, 10);
	to   = strtobase(argv[1], 1, SSIZE_MAX, 10);

	chrp  = 1;
	for (; from < to; from++) {
		i    = 1;
		ndiv = 0;

		for (; i < from; i++) {
			if (!(i % from) && (i != 1 && i != from)) {
				ndiv++;
				break;
			}
		}

		if (ndiv)
			continue;

		if ((chrp += numlen(from) + SAFEZON) > COLUMNS) {
			putchar('\n');
			chrp  = 1;
		}

		printf("%zd", from);

		if ((from + 1) < to)
			putchar('\t');
	}
	putchar('\n');

	return 0;
}

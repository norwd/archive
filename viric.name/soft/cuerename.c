/*
 * cuebreakpoints.c -- print track break points
 *
 * Copyright (C) 2004, 2005, 2006 Svend Sorensen
 * For license terms, see the file COPYING in this distribution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cuefile.h"
#include "time.h"

char *progname;
char *suffix;


void usage (int status)
{
	if (0 == status) {
		fprintf(stdout, "%s: usage: cuerenae [cuefile] [split-track%%02i. suffix]\n", progname);
	} else {
		fprintf(stderr, "run `%s --help' for usage\n", progname);
	}

	exit (status);
}

void print_renames (Cd *cd)
{
	int i;
	long b;
	long pg;
	Track *track;
    Cdtext *cdtext;

	for (i = 1; i <= cd_get_ntrack(cd); i++) {
		track = cd_get_track(cd, i);

        cdtext = track_get_cdtext(track);

        printf("mv split-track%02i.%s \"%02i - %s - %s.%s\"\n", i,
                suffix, i,
                cdtext_get(PTI_PERFORMER, cdtext),
                cdtext_get(PTI_TITLE, cdtext), suffix);
	}
}

int renames (char *name, int format)
{
	Cd *cd = NULL;

	if (NULL == (cd = cf_parse(name, &format))) {
		fprintf(stderr, "%s: input file error\n", name);
		return -1;
	}

	print_renames(cd);

	return 0;
}

int main (int argc, char **argv)
{
	int format = UNKNOWN;

	/* option variables */
	char c;
	/* getopt_long() variables */
	extern char *optarg;
	extern int optind;

	progname = *argv;

    suffix = "wav";
    if (argc > 2)
        suffix = argv[2];

	if (argc == 1) {
		renames("-", format);
	} else {
		for (; optind < argc; optind++)
			renames(argv[1], format);
	}

	return 0;
}

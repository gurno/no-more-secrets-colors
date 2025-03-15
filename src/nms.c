/*
 * Copyright (c) 2017 Brian Barto
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GPL License. See LICENSE for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "nmseffect.h"
#include "input.h"
#include "error.h"

#define VERSION "1.0.1"

int main(int argc, char *argv[])
{
	int r, o;
	unsigned char *input;

	input = NULL;

	while ((o = getopt(argc, argv, "f:ascvt:j:J:r:h")) != -1)
	{
		switch (o)
		{
			case 'f':
				nmseffect_set_foregroundcolor(optarg);
				break;
			case 'a':
				nmseffect_set_autodecrypt(1);
				break;
			case 's':
				nmseffect_set_maskblank(1);
				break;
			case 'c':
				nmseffect_set_clearscr(1);
				break;
			case 't':
				nmseffect_set_type_speed(atoi(optarg));
				break;
			case 'j':
				nmseffect_set_jumble_seconds(atoi(optarg));
				break;
			case 'J':
				nmseffect_set_jumble_speed(atoi(optarg));
				break;
			case 'r':
				nmseffect_set_reveal_speed(atoi(optarg));
				break;
			case 'v':
				printf("nms version " VERSION "\n");
				return EXIT_SUCCESS;
			case 'h':
				printf("Usage: nms [OPTIONS]\n\n");
				printf("Options:\n");
				printf("  -f COLOR\tSet foreground color (white, yellow, magenta, blue, green, red, cyan)\n");
				printf("  -a\t\tAuto-decrypt (no key press required)\n");
				printf("  -s\t\tMask blank spaces\n");
				printf("  -c\t\tClear screen before showing output\n");
				printf("  -t MS\t\tSet type effect speed (milliseconds per character, default: 4)\n");
				printf("  -j SEC\tSet jumble effect duration (seconds, default: 2)\n");
				printf("  -J MS\t\tSet jumble effect speed (milliseconds per update, default: 35)\n");
				printf("  -r MS\t\tSet reveal effect speed (milliseconds per update, default: 50)\n");
				printf("  -v\t\tDisplay version information\n");
				printf("  -h\t\tDisplay this help message\n");
				return EXIT_SUCCESS;
			case '?':
				if (isprint(optopt))
				{
					error_log("Unknown option '-%c'.", optopt);
				}
				else
				{
					error_log("Unknown option character '\\x%x'.", optopt);
				}
				error_print();
				return EXIT_FAILURE;
		}
	}

	r = input_get(&input, "Enter input: ");
	if (r < 0)
	{
		error_log("Could not get input.");
		error_print();
		return EXIT_FAILURE;
	}
	else if (r == 0)
	{
		error_log("Input is empty.");
		error_print();
		return EXIT_FAILURE;
	}

	r = nmseffect_exec(input, r);

	free(input);

	return EXIT_SUCCESS;
}

/*
 * Copyright (c) 2017 Brian Barto
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GPL License. See LICENSE for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include "nmseffect.h"

#define VERSION "1.0.1"

int main(int argc, char *argv[]) {
	int o;
	int termCols, spaces = 0;
	unsigned char *display_uc = NULL;
	char *display        = NULL;
	char *head1Left      = "DATANET PROC RECORD:  45-3456-W-3452";
	char *head1Right     = "Transnet on/xc-3";
	char *head2Center    = "FEDERAL RESERVE TRANSFER NODE";
	char *head3Center    = "National Headquarters";
	char *head4Center    = "************  Remote Systems Network Input Station  ************";
	char *head5Center    = "================================================================";
	char *menu1          = "[1] Interbank Funds Transfer  (Code Prog: 485-GWU)";
	char *menu2          = "[2] International Telelink Access  (Code Lim: XRP-262)";
	char *menu3          = "[3] Remote Facsimile Send/Receive  (Code Tran:  2LZP-517)";
	char *menu4          = "[4] Regional Bank Interconnect  (Security Code:  47-B34)";
	char *menu5          = "[5] Update System Parameters  (Entry Auth. Req.)";
	char *menu6          = "[6] Remote Operator Logon/Logoff";
	char *foot1Center    = "================================================================";
	char *foot2Center    = "[ ] Select Option or ESC to Abort";
	
	// Process command line options
	while ((o = getopt(argc, argv, "f:ascvt:j:J:r:h")) != -1) {
		switch (o) {
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
				printf("sneakers version " VERSION "\n");
				return EXIT_SUCCESS;
			case 'h':
				printf("Usage: sneakers [OPTIONS]\n\n");
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
				if (isprint(optopt)) {
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				} else {
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				}
				return EXIT_FAILURE;
		}
	}

	// Get terminal dimentions (needed for centering)
	struct winsize w;
    // if not an interactive tty, w is not populated, resulting in UB
	if (ioctl(0, TIOCGWINSZ, &w) == -1) {
        perror("Input not from an interactive terminal");
        return 1;
    }
	termCols = w.ws_col;

	// Allocate space for our display string
	if ((display = malloc(20 * termCols)) == NULL)
	{
		fprintf(stderr, "Memory Allocation Error. Quitting!\n");
		return 1;
	}

	// Allocate space for our display string
	if ((display_uc = malloc(20 * termCols)) == NULL)
	{
        free(display);
		fprintf(stderr, "Memory Allocation Error. Quitting!\n");
		return 1;
	}

	memset(display, 0, 20 * termCols);
	memset(display_uc, 0, 20 * termCols);

	// Start building the display string
	strcpy(display, head1Left);

	spaces = termCols - strlen(head1Left) - strlen(head1Right);
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, head1Right);

	strcat(display, "\n");

	spaces = (termCols - strlen(head2Center)) / 2;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, head2Center);

	strcat(display, "\n");
	strcat(display, "\n");

	spaces = (termCols - strlen(head3Center)) / 2;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, head3Center);

	strcat(display, "\n");
	strcat(display, "\n");

	spaces = (termCols - strlen(head4Center)) / 2;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, head4Center);

	strcat(display, "\n");

	spaces = (termCols - strlen(head5Center)) / 2;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, head5Center);

	strcat(display, "\n");
	strcat(display, "\n");

	spaces = ((termCols - strlen(head5Center)) / 2) + 3;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, menu1);

	strcat(display, "\n");

	spaces = ((termCols - strlen(head5Center)) / 2) + 3;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, menu2);

	strcat(display, "\n");

	spaces = ((termCols - strlen(head5Center)) / 2) + 3;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, menu3);

	strcat(display, "\n");

	spaces = ((termCols - strlen(head5Center)) / 2) + 3;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, menu4);

	strcat(display, "\n");

	spaces = ((termCols - strlen(head5Center)) / 2) + 3;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, menu5);

	strcat(display, "\n");

	spaces = ((termCols - strlen(head5Center)) / 2) + 3;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, menu6);

	strcat(display, "\n");
	strcat(display, "\n");

	spaces = (termCols - strlen(foot1Center)) / 2;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, foot1Center);

	strcat(display, "\n");
	strcat(display, "\n");

	spaces = (termCols - strlen(foot2Center)) / 2;
	while (spaces > 0) {
		strcat(display, " ");
		--spaces;
	}
	strcat(display, foot2Center);

	// Default setting for sneakers is to clear the screen
	nmseffect_set_clearscr(1);

	memcpy(display_uc, display, 20 * termCols);

	// Execute effect
	nmseffect_exec(display_uc, strlen(display));

	free(display);
	free(display_uc);

	return 0;
}
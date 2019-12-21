/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Sat Dec 21 11:12:33 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"
#include "grid.h"

extern int g_quiet;//access_global

//This is shit I will fix that later
unsigned int get_line_count(char *cword) {
	unsigned int line_count = 1;

	if (!cword || !strlen(cword) || !strcmp(cword, "\n")) {
		return (0);
	}

	for (int i = 0; cword[i]; i++) {
		if (cword[i] == '\n'
				&& cword[i + 1] != '\0'
				&& cword[i + 1] != '\n') {
			line_count++;
		}
	}

	return (line_count);
}

int puzzled(int n, int m, char *dict_file) {
	char *dict = NULL;
	char **words = NULL;
	unsigned int line_count = 0;

	printf("puzzled is running with N = [%d] && M = [%d]\n", n, m); // Debug

	if (!(dict = getfile(dict_file))) {
		printf("Error: dict: set to NULL");
		return (-1);
	}

	line_count = get_line_count(dict);
	words = set_grid(dict, line_count);
	if (!g_quiet) {
		show_grid(words); // Debug
	}
	printf("dict words: %d", line_count); // Debug

	free(dict);
	return (0);
}

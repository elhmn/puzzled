/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Thu Dec 26 14:51:46 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"
#include "grid.h"
#include "color.h"
#include "dict.h"

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
	t_dict dict;
	char *s_dict = NULL;
	char **words = NULL;
	char **cwgrid = NULL;
	unsigned int line_count = 0;

	printf("crossword generator is running with N = [%d] && M = [%d] ...\n", n, m);

	if (!(s_dict = getfile(dict_file))) {
		printf("Error: dict: set to NULL");
		return (-1);
	}

	line_count = get_line_count(s_dict);
	words = set_grid(s_dict, line_count);

	printf("\ninitaliase dictionnary...\n");

	if (init_dict(n, m, words, line_count, &dict) == -1) {
		printf(COLOR_RED
		"failed to initalise dictionnary\n"
		COLOR_RESET);
	}

	if (!g_quiet) {
		printf("dictionnary file line count: %d\n", line_count);
		dump_dict(dict);
	}
	printf("dictionnary initialised\n\n");

	if (dict.maxlen < (n > m ? n : m)) {
		printf(COLOR_RED
		"unable to create a grid : longest word (len = %d) in the dictionnary is smaller than max(m, n) \n"
		COLOR_RESET, dict.maxlen);
	} else if (dict.minlen / 2 >= ((n < m ? n : m) - 1) * 2) {
		printf(COLOR_RED
		"unable to create a grid : shortest word (len = %d) in the dictionnary is smaller than 2 * (min(m, n) + 1) \n"
		COLOR_RESET, dict.minlen);
	} else {

		printf("bruteforce is running...\n");
		cwgrid = bruteforce(n, m, dict);
		printf("bruteforce done...\n\n");

		show_grid(cwgrid);
	}

	free(s_dict);
	free_dict(&dict);
	free(words);
	free_grid(&cwgrid);
	return (0);
}

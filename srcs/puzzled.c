/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Sun Jan 12 17:41:10 2020                        by elhmn        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"
#include "grid.h"
#include "color.h"
#include "dict.h"


#ifdef __EMSCRIPTEN__

# include <SDL/SDL.h>
# include <emscripten.h>
# include "wasm.h"

#endif //__EMSCRIPTEN__

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

int puzzled(int m, int n, char *dict_file) {
	t_dict dict;
	char *s_dict = NULL;
	char **words = NULL;
	unsigned int line_count = 0;

	printf("crossword generator is running with M = [%d] && N = [%d] ...\n", m, n);

	if (!(s_dict = getfile(dict_file))) {
		printf("Error: dict: set to NULL");
		return (-1);
	}

	line_count = get_line_count(s_dict);
	words = set_grid(s_dict, line_count);

	printf("\ninitaliase dictionnary...\n");

	if (init_dict(m, n, words, line_count, &dict, dict_file) == -1) {
		printf(COLOR_RED
				"failed to initalise dictionnary\n"
				COLOR_RESET);
	}

	if (!g_quiet) {
		printf("dictionnary file line count: %d\n", line_count);
		dump_dict(dict);
	}
	printf("dictionnary initialised\n\n");

	if (dict.maxlen < MAX(m, n)) {
		printf(COLOR_RED
				"unable to create a grid : longest word (len = %d) in the dictionnary is smaller than max(m, n) \n"
				COLOR_RESET, dict.maxlen);
	} else if (dict.minlen / 2 >= (MIN(m, n) - 1) * 2) {
		printf(COLOR_RED
				"unable to create a grid : shortest word (len = %d) in the dictionnary is greater than 4 * (min(m, n) - 1) \n"
				COLOR_RESET, dict.minlen);
	} else {
		bruteforce(m, n, dict);
	}

	free(s_dict);
	free_dict(&dict);
	free(words);
	return (0);
}

#ifdef __EMSCRIPTEN__
int emcc_puzzled(int m, int n, char *dict_file) {
	t_dict dict;
	char *s_dict = NULL;
	char **words = NULL;
	unsigned int line_count = 0;

	printf("crossword generator is running with M = [%d] && N = [%d] ...\n", m, n);

	if (!(s_dict = getfile(dict_file))) {
		printf("Error: dict: set to NULL");
		return (-1);
	}

	line_count = get_line_count(s_dict);
	words = set_grid(s_dict, line_count);

	printf("\ninitaliase dictionnary...\n");

	if (init_dict(m, n, words, line_count, &dict, dict_file) == -1) {
		printf(COLOR_RED
				"failed to initalise dictionnary\n"
				COLOR_RESET);
	}

	if (!g_quiet) {
		printf("dictionnary file line count: %d\n", line_count);
		dump_dict(dict);
	}
	printf("dictionnary initialised\n\n");

	if (dict.maxlen < MAX(m, n)) {
		printf(COLOR_RED
				"unable to create a grid : longest word (len = %d) in the dictionnary is smaller than max(m, n) \n"
				COLOR_RESET, dict.maxlen);
	} else if (dict.minlen / 2 >= (MIN(m, n) - 1) * 2) {
		printf(COLOR_RED
				"unable to create a grid : shortest word (len = %d) in the dictionnary is greater than 4 * (min(m, n) - 1) \n"
				COLOR_RESET, dict.minlen);
	} else {
		emscripten_async_call(emcc_bruteforce, &(t_brute){
				.dict = dict,
				.m = m,
				.n = n,
				}, 1000);
  		emscripten_set_main_loop(wasm_loop, 60, 1);
	}

	free(s_dict);
	free_dict(&dict);
	free(words);
	return (0);
}
#endif

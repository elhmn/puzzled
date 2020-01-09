/* ************************************************************************** */
/*                                                                            */
/*  bruteforce.c                                                              */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Tue Dec 24 15:44:04 2019                        by elhmn        */
/*   Updated: Thu Jan 09 16:52:37 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "grid.h"
#include "color.h"
#include "puzzled.h"

extern int g_interactive;
extern int g_output;
extern unsigned int g_limit;

int grid_correct(char **grid, t_dict dict, int rc, int cc) {
	int row;

	if (!grid) {
		return (-1);
	}

	if ((row = check_at_least_one_blank_rc_cc(grid, rc, cc)) >= 0) {
		return (-2);
	}
	if ((row = check_row_and_col_filled_at_50_per_cent_rc_cc(grid, rc, cc)) >= 0) {
		return (-3);
	}
	if ((row = check_no_duplicated_words_rc_cc(grid, rc, cc)) >= 0) {
		return (-4);
	}
	if ((row = check_words_belong_to_dictionnary(grid, dict, rc, cc)) >= 0) {
		return (-5);
	}

	return (0);
}

void put_word(char *word, char **grid, int rc, int cc, int i) {
	int wlen;

	if (grid && word) {
		if (rc < 0) {
			rc = get_grid_row_count(grid);
		}

		if (i < rc ) {
			wlen = strlen(word);
			if (cc < 0) {
				cc = strlen(grid[i]);
			}

			if (wlen <= cc)
				strncpy(grid[i], word, wlen);
		}
	}
}

void remove_word(char *word, char **grid, int rc, int cc, int i) {
	int wlen;

	if (grid) {
		if (rc < 0) {
			rc = get_grid_row_count(grid);
		}


		if (i < rc) {
			wlen = strlen(word);
			if (cc < 0) {
				cc = strlen(grid[i]);
			}
			memset(grid[i], EMPTY, cc < wlen ? cc : wlen);
		}
	}
}

int was_placed(int *placed, int len, int w_i) {
	for (int i = 0; i < len; i++) {
		if (placed[i] == w_i) {
			return (0);
		}
	}
	return (-1);
}

int find_word(char *str, char *to_search) {
	regex_t regex;
	int reti;
	char msgbuf[100];
	char pattern[1000] = "^"; //word in dictionnary must not be longer than that

	strcat(pattern, str);
	reti = regcomp(&regex, pattern, 0);
	if (reti) {
    	fprintf(stderr, "Could not compile regex\n");
    	return (-1);
	}

	/* Execute regular expression */
	reti = regexec(&regex, to_search, 0, NULL, 0);
	if (!reti) {
		return (0);
	}
	else if (reti == REG_NOMATCH) {
		return (-1);
	}
	else {
    	regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    	fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    	return (-1);
	}

	return (0);
}

int has_valid_col(t_dict *dict, char **grid, int rc, int cc) {
    char **words;
    int wcount;

    if (!dict || !grid) {
        return (-1);
    }

    if (!(words = get_vertical_words(grid, rc, cc))) {
        return (-1);
    }

    wcount = get_grid_row_count(words);
    for (int i = 0; i < wcount; i++) {
    	if (!words[i] || !strcmp(words[i], "")) {
    		continue;
    	}

        if (search_word_hash(dict->col_hash, words[i]) < 0) {
            free_grid(&words);
            return (-1);
        }
    }

    free_grid(&words);
    return (0);
}


long double factorial(long double n) {
	if (!n) {
		return (1);
	}
	return (n * factorial(n - 1));
}

unsigned long get_possible_combination_count(int wlen, int rc) {
	unsigned long wcells = wlen / 2;
	unsigned long rcells = rc / 2;

	(void)wcells;
	(void)rcells;

	return (factorial(rcells)
			/ (factorial(rcells - wcells) * factorial(wcells)));
}

void gen_combinations(char **comb,
		unsigned int *comb_count,
		char *word, int wlen,
		int cc, char *row,
		int cell, int cell_pos) {
	int prev[2], cur[2] = {0};
	char *snapshot_1 = NULL;
	char *snapshot_2 = NULL;

	prev[0] = cell_pos;
	prev[1] = cell_pos + 1;
	cur[0] = cell_pos + 2;
	cur[1] = cell_pos + 3;

	if (cell < 0) {
		return;
	}

	if (cell_pos + 2 + (int)strlen(word + cell * 2) > cc) {
		return ;
	}

	if (prev[0] != 0 && row[cur[0]] != EMPTY) {
		return ;
	}

	row[prev[0]] = EMPTY;
	row[prev[1]] = EMPTY;
	row[cur[0]] = word[cell * 2];
	row[cur[1]] = word[cell * 2 + 1];

	if (!(snapshot_1 = strdup(row))) {
		printf("failed to allocate snapshot_1\n");
		return ;
	}
	if (!(snapshot_2 = strdup(row))) {
		printf("failed to allocate snapshot_2\n");
		return ;
	}

	if (!(comb[*comb_count] = strdup(row))) {
		printf("failed to allocate comb[]\n");
		return ;
	}

	(*comb_count)++;
	gen_combinations(comb, comb_count, word, wlen, cc, snapshot_1, cell, cell_pos + 2);
	gen_combinations(comb, comb_count, word, wlen, cc, snapshot_2, cell - 1, cell * 2 - 2);

	free(snapshot_1);
	free(snapshot_2);
	return;
}

char *format(char *filename) {
	char *f;

	if (!(f = filename)) {
		return ("");
	}
	while (*f) {
		if (*f == '/') {
			*f = '_';
		}
		f++;
	}
	return (filename);
}

int save_crossword(t_dict dict, char **grid, int rc, int cc, unsigned int gcount) {
	char *buf;
	char file[300] = "";

	if (!(buf = calloc(rc * (cc + 2), sizeof(char)))) {
		return (-1);
	}

	sprintf(file, "%sgrid_%s_%d_%d_%d.gen", GENERATED_CW_FOLDER, format(dict.file), rc, cc, gcount);

	store_grid(buf, grid);
	if (putfile(file, buf) < 0) {
		return (-1);
	}

	free(buf);
	return (0);
}

void backtracking(t_dict *dict, char **grid,
		int rc, int cc, int i, unsigned int *gcount) {
	char *tmp = NULL;
	char **words = NULL;

	if (i >= rc) {
		if (grid_correct(grid, *dict, rc, cc) >= 0) {
			printf("Crossword generated:\n");
			words = get_words(grid);
			*gcount += 1;
			if (words) {
				show_grid(words);
				free_grid(&words);
				printf("\n");
			}
			printf("\n");
			show_grid(grid);
			printf("\n");

			if (g_interactive) {
				char buf[4];
				printf("Continue ? (y/n)\n");
				scanf("%s", buf);
				if (!strcmp(buf, "n")) {
					exit(0);
				}
			} else {
				if (g_output) {
					save_crossword(*dict, grid, rc, cc, *gcount);
					printf("crossword was saved\n");
				}

				if (g_limit != 0 && *gcount >= g_limit) {
					printf("%d crosswords were genereated\n", *gcount);
					exit(0);
				}
			}

			printf("Searching for other crossword...\n");
		}
		return;
	}

	if (i > 1 && has_valid_col(dict, grid, rc, cc) < 0) {
		return ;
	}

	for (int w = 0; w < dict->wcount; w++) {

		if (!dict->comb[w]) {
			continue;
		}

		if (was_placed(dict->placed_w, rc, w) >= 0) {
			continue;
		}

		for (int comb = 0; dict->comb[w][comb]; comb++) {
			tmp = grid[i];
			dict->placed_w[i] = w;
			grid[i] = dict->comb[w][comb];
			backtracking(dict, grid, rc, cc, i + 1, gcount);
			grid[i] = tmp;
			dict->placed_w[i] = -1;
		}
	}
	return ;
}


char **bruteforce(int m, int n, t_dict dict) {
	char **grid = NULL;
	char **dwords = NULL;
	char *row = NULL;
	char *word = NULL;
	int wlen = 0;
	unsigned int comb_count = 0;
	unsigned int total_comb_count = 0;
	unsigned int gcount = 0;

	if (!(grid = new_grid_uni_dimension(m))) {
		printf(COLOR_RED
				"failed to initialise new crossword grid\n"
				COLOR_RESET);
		return (NULL);
	}

	dwords = dict.words;

	if (!(row = (char*)malloc(sizeof(char) * (n * 2 + 1)))) {
		return (NULL);
	}
	row[n * 2] = '\0';

	printf("Generating every combinations...\n");
	for (int i = 0; i < dict.wcount; i++) {
		memset(row, EMPTY, n * 2);
		word = dict.words[i];
		wlen = strlen(word);
		if (wlen > n * 2) {
			continue;
		}
		strncpy(row, word, wlen);

		//initialise list of combinations
		if (dict.comb) {
			comb_count = get_possible_combination_count(wlen, n * 2);
			if (!(dict.comb[i] = (char**)malloc(sizeof(char*) * (comb_count + 1)))) {
				return (NULL);
			}
			for (unsigned int j = 0; j <= comb_count; j++) {
				dict.comb[i][j] = NULL;
			}
			dict.comb[i][0] = strdup(row);
		}

		comb_count = 1;
		gen_combinations(dict.comb[i], &comb_count,
				word, wlen, n * 2, row, (wlen - 1) / 2, wlen - 2);
		dict.comb_count[i] = comb_count;
		total_comb_count += comb_count;
	}
	free(row);
	printf("%d combinations generated\n", total_comb_count);
	printf("Bactracking is running...\n");
	backtracking(&dict, grid, m, n * 2, 0, &gcount);
	printf("Bactracking is done\n");

	return (grid);
}

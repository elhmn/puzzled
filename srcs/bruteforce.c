/* ************************************************************************** */
/*                                                                            */
/*  bruteforce.c                                                              */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Tue Dec 24 15:44:04 2019                        by elhmn        */
/*   Updated: Tue Jan 07 03:14:27 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "grid.h"
#include "color.h"
#include "puzzled.h"

int grid_correct(char **grid, t_dict dict) {
	int row;

	(void)dict;
	if (!grid) {
		return (-1);
	}

	if ((row = check_at_least_one_blank(grid)) >= 0) {
		return (-2);
	}
	else if ((row = check_row_and_col_filled_at_50_per_cent(grid)) >= 0) {
		return (-3);
	}
	else if ((row = check_no_duplicated_words(grid)) >= 0) {
		return (-4);
	}
	else if ((row = check_words_belong_to_dictionnary(grid, dict)) >= 0) {
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

int get_next_word_index(t_dict *dict, int w_i, int rc, int cc) {
	int i, wcount;

	i = 0;
	wcount = dict->wcount;
	while (i <= wcount) {
		if (was_placed(dict->placed_w, rc, i) < 0 && w_i != i) {
			return (i);
		}
		i++;
	}
	(void)cc;
	return w_i;
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

int has_valid_col(t_dict *dict, char **grid) {
       char **words;
       int wcount;
       int idx_start, idx_end;

       if (!dict || !grid) {
               return (-1);
       }

       if (!(words = get_vertical_words(grid))) {
               return (-1);
       }

       wcount = get_grid_row_count(words);

       for (int i = 0; i < wcount; i++) {
               if ((idx_start = get_start_index(dict, words[i])) < 0) {
                       continue ;
               }
               if ((idx_end = get_end_index(dict, words[i])) < 0) {
                       continue ;
               }
               if (strlen(words[i]) <= 0) {
                       continue ;
               }

               for (int j = idx_start; j < idx_end; j++) {
                       if (find_word(words[i], dict->words[j]) >= 0) {
                               free_grid(&words);
                               return (0);
                       }
               }
       }

       free_grid(&words);
       return (-1);
}

void backtracking(t_dict *dict, char **grid,
		int rc, int cc, int i, int w_i, int comb_i) {
	char *tmp = NULL;
	char **words = NULL;

	printf("\n"); // Debug
	show_grid(grid); // Debug
	printf("\n"); // Debug

	if (i >= rc) {
		if (grid_correct(grid, *dict) >= 0) {
			printf("Crossword generated:\n");
			words = get_words(grid);
			if (words) {
				show_grid(words);
				free_grid(&words);
				printf("\n");
			}
			printf("\n");
			show_grid(grid);
			printf("\n");

			char buf[4];
			printf("Continue ? (y/n)\n");
			scanf("%s", buf);
		}
		return;
	}

	(void)w_i;
	(void)comb_i;
	for (int w = 0; w < dict->wcount; w++) {
		if (was_placed(dict->placed_w, rc, w) >= 0) {
			continue;
		}

		for (int comb = 0; dict->comb[w][comb]; comb++) {
			tmp = grid[i];

			dict->placed_w[i] = w;
			grid[i] = dict->comb[w][comb];
			backtracking(dict, grid, rc, cc, i + 1, 0, 0);
			grid[i] = tmp;
			dict->placed_w[i] = -1;
		}
	}
	return ;
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

	snapshot_1 = strdup(row);
	snapshot_2 = strdup(row);

	comb[*comb_count] = snapshot_1;
	(*comb_count)++;
	gen_combinations(comb, comb_count, word, wlen, cc, snapshot_1, cell, cell_pos + 2);
	gen_combinations(comb, comb_count, word, wlen, cc, snapshot_2, cell - 1, cell * 2 - 2);

	free(snapshot_2);
	return;
}

char **bruteforce(int m, int n, t_dict dict) {
	char	**grid = NULL;
	char	**dwords = NULL;
	char	*row = NULL;

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

	char *word = NULL;
	int wlen = 0;
	unsigned int comb_count = 0;

	for (int i = 0; i < dict.wcount; i++) {
		memset(row, EMPTY, n * 2);
		word = dict.words[i];
		wlen = strlen(word);
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
	}
	free(row);

	backtracking(&dict, grid, m, n * 2, 0, 0, 0);
	return (grid);
}


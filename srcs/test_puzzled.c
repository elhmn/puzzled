/* ************************************************************************** */
/*                                                                            */
/*  test_puzzled.c                                                            */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:01:37 2019                        by elhmn        */
/*   Updated: Sat Dec 21 10:23:52 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"
#include "grid.h"
#include "color.h"

extern int g_quiet;//access_global

//returns 0 or failing line in case of failure
int check_row_size(char **grid) {
	int len;
	int prevlen;

	if (!grid) {
		return (0);
	}

	len = strlen(grid[0]);
	prevlen = len;
	for (int i = 1; grid[i]; i++) {
		if (prevlen != (len = strlen(grid[i]))) {
			return (i + 1);
		}
	}

	return (-1);
}

//returns 0 or failing line in case of failure
int check_wrong_character(char **grid) {
	char c;

	if (!grid) {
		return (0);
	}

	for (int i = 0; grid[i]; i++) {
		for (int j = 0; (c = grid[i][j]); j++) {
			if (!((c >= 'a' && c <= 'z') || c == EMPTY)) {
				return (i + 1);
			}
		}
	}

	return (-1);
}


//returns 0 or failing line in case of failure
int check_at_least_one_blank(char **grid) {
	char c;
	int	 found;
	int i, j;

	if (!grid) {
		return (0);
	}

	//Check for at list one empty block in a row
	for (i = 0; grid[i]; i++) {
		found = 0;

		for (j = 0; (c = grid[i][j]); j++) {
			if (c == EMPTY) {
				found = 1;
			}
		}

		if (!found) {
			return (i + 1);
		}
	}

	//Check for at list one empty block in a column
	i = 0;
	for (j = 0; grid[i] && grid[i][j]; j++) {
		found = 0;

		for (i = 0; grid[i] && (c = grid[i][j]); i++) {
			if (c == EMPTY) {
				found = 1;
			}
		}

		if (!found) {
			return (i + 1);
		}
	}

	return (-1);
}


//returns 0 or failing line in case of failure
int check_row_and_col_filled_at_50_per_cent(char **grid) {
	char c;
	int found;
	int i, j;

	if (!grid) {
		return (0);
	}

	//Check that the row is filled at more than 50%
	for (i = 0; grid[i]; i++) {
		found = 0;

		for (j = 0; (c = grid[i][j]); j++) {
			if (c == EMPTY) {
				found++;
			}
		}

		if (found > j / 2) {
			return (i + 1);
		}
	}

	//Check that the row is filled at more than 50%
	i = 0;
	for (j = 0; grid[i] && grid[i][j]; j++) {
		found = 0;

		for (i = 0; grid[i] && (c = grid[i][j]); i++) {
			if (c == EMPTY) {
				found++;
			}
		}

		if (found > i / 2) {
			return (i + 1);
		}
	}

	return (-1);
}

//returns index of next letter in `i` row
int get_next_letter_in_row(char **grid, int i, int j) {
	char c = '\0';

	if (grid && grid[i]) {
		while ((c = grid[i][j])) {
			if (c >= 'a' && c <= 'z') {
				break;
			}
			j++;
		}
	}

	return (j);
}

char **new_words_list(char **grid) {
	char **words = NULL;
	int row_count = 0;
	int col_count = 0;
	int words_count = 0;
	int words_max_len = 0;

	row_count = get_grid_row_count(grid);
	col_count = get_grid_col_count(grid);

	//get the maximum count of words present in a grid
	words_count = row_count + (col_count / 2);

	//get the maximum count of line a word can have
	words_max_len = row_count * 2;
	if (row_count < col_count) {
		words_max_len = col_count;
	}

	if (!(words = (char**)malloc(sizeof(char*) * (words_count + 1)))) {
		return (NULL);
	}
	words[words_count] = NULL;

	for (int i = 0; i < words_count; i++) {
		if (!(words[i] = (char*)malloc(sizeof(char) * (words_max_len + 1)))) {
			return (NULL);
		}
		words[i][words_max_len] = '\0';
	}

	return (words);
}

//returns word grid
char **get_words(char **grid) {
	char **words = NULL;
	char c;
	int i, j;
	int k, l;
	int m, n;

	if (!grid) {
		return (NULL);
	}

	if (!(words = new_words_list(grid))) {
		return (NULL);
	}

	//Get horizontal words
	i = -1;
	k = -1;
	while (grid[++i]) {
		++k;
		l = -1;
		j = -1;
		while (grid[i][++j]) {
			j = get_next_letter_in_row(grid, i, j);
			if ((c = grid[i][j]) != -1) {
				words[k][++l] = c;
			}
		}
		words[k][++l] = '\0';
	}

	//Get vertical words
	i = 0;
	j = -2;
	while (grid[i] && grid[i][(j += 2)]) {
		m = 0;
		n = j;
		l = 0;
		++k;
		while (grid[m] && grid[m][n]) {
			c = grid[m][n];
			if (c >= 'a' && c <= 'z') {
				words[k][l] = c;
				l++;
			}
			m = (n % 2) ? m + 1 : m;
			n++;
			n = (n % 2) ? j + 1 : j;
		}
		words[k][l] = '\0';
	}

	return (words);
}

//returns 0 or failing line in case of failure
int check_no_duplicated_words(char **grid) {
	char **words = NULL;
	int i, j;

	if (!grid) {
		return (0);
	}

	if (!(words = get_words(grid))) {
		printf("Error: could not allocate words\n");
		return (0);
	}
	i = 0;
	while (words[i]) {
		j = i + 1;
		while (words[j]) {
			if (!strcmp(words[i], words[j])) {
				return (j);
			}
			j++;
		}
		i++;
	}

	free_grid(&words);
	return (-1);
}

//returns 0 or failing line in case of failure
int check_row_lenght_not_even(char **grid) {
	if (!grid) {
		return (0);
	}

	for (int i = 0; grid[i]; i++) {
		if (strlen(grid[i]) % 2) {
			return (i + 1);
		}
	}

	return (-1);
}

//returns 0 or failing line in case of failure
int check_square_of_2_letter_or_2_empty_blocks(char **grid) {
	char c, p;

	if (!grid) {
		return (0);
	}

	for (int i = 0; grid[i]; i++) {
		for (int j = 0; (c = grid[i][j]); j++) {
			if (j % 2 != 0) {
				p = grid[i][j - 1];

				//If [j - 1] capitalised && [j] !capitalised
				if (p >= 'a' && p <= 'z' && !(c >= 'a' && c <= 'z')) {
					return (i + 1);
				}

				//If [j - 1] empty && [j] !empty
				if (p == EMPTY && c != EMPTY) {
					return (i + 1);
				}
			}
		}
	}
	return (-1);
}

int test_puzzled(char *cword_file) {
	int row;
	char *cword = NULL;
	char **grid = NULL;
	unsigned int line_count = 0;


	if (!(cword = getfile(cword_file))) {
		printf("Error: cword: set to NULL");
		return (-1);
	}

	line_count = get_line_count(cword);
	grid = set_grid(cword, line_count);

	if (!g_quiet) {
		show_grid(grid);
	}

	printf("Running tests...\n");
	if ((row = check_row_size(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: row size : make sure every line has the same size\n"
		COLOR_RESET, row);
	}
	else if ((row = check_row_lenght_not_even(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: row size not even\n"
		COLOR_RESET, row);
	}
	else if ((row = check_wrong_character(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: wrong character: characters must be uncapitalised letters or `%c` \n"
		COLOR_RESET, row, EMPTY);
	}
	else if ((row = check_square_of_2_letter_or_2_empty_blocks(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: each square must contain 2 letters or 2 empty blocks \n"
		COLOR_RESET, row);
	}
	else if ((row = check_at_least_one_blank(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: each column and row must contain at least one blank\n"
		COLOR_RESET, row);
	}
	else if ((row = check_row_and_col_filled_at_50_per_cent(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: each column and row must be filled more than 50 percent \n"
		COLOR_RESET, row);
	}
	else if ((row = check_no_duplicated_words(grid)) >= 0) {
		printf(COLOR_RED
		"failed: at row[%d]: no duplicated words \n"
		COLOR_RESET, row);
	}

	//free memory
	free(cword);
	free(grid);

	//failed
	if (row >= 0) {
		exit(EXIT_FAILURE);
	}

	printf(COLOR_GREEN "Congratulations your puzzler is valid !!\n" COLOR_RESET);

	return (0);
}

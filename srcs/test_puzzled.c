/* ************************************************************************** */
/*                                                                            */
/*  test_puzzled.c                                                            */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:01:37 2019                        by elhmn        */
/*   Updated: Wed Dec 18 14:19:39 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

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

char **set_map(char *src, unsigned int size) {
	char **map = NULL;

	if (!src) {
		return (NULL);
	}

	if (!(map = (char**)malloc(sizeof(char*) * (size + 1)))) {
		return (NULL);
	}
	*(map + size) = NULL;

	int i = 0;
	*(map + i) = strtok(src, "\n");
	while (*(map + i++)) {
		*(map + i) = strtok(NULL, "\n");
	}
	return (map);
}

void show_map(char** map) {
	if (!map) {
		return ;
	}
	for (int i = 0; map[i]; i++) {
		printf("[%s]\n", map[i]);
	}
}

//returns 0 or failing line in case of failure
int check_row_size(char **map) {
	int len;
	int prevlen;

	if (!map) {
		return (0);
	}

	len = strlen(map[0]);
	prevlen = len;
	for (int i = 1; map[i]; i++) {
		if (prevlen != (len = strlen(map[i]))) {
			return (i + 1);
		}
	}

	return (-1);
}

//returns 0 or failing line in case of failure
int check_wrong_character(char **map) {
	char c;

	if (!map) {
		return (0);
	}

	for (int i = 0; map[i]; i++) {
		for (int j = 0; (c = map[i][j]); j++) {
			if (!((c >= 'a' && c <= 'z') || c == EMPTY)) {
				return (i + 1);
			}
		}
	}

	return (-1);
}


//returns 0 or failing line in case of failure
int check_at_least_one_blank(char **map) {
	char c;
	int	 found;
	int i, j;

	if (!map) {
		return (0);
	}

	//Check for at list one empty block in a row
	for (i = 0; map[i]; i++) {
		found = 0;

		for (j = 0; (c = map[i][j]); j++) {
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
	for (j = 0; map[i] && map[i][j]; j++) {
		found = 0;

		for (i = 0; map[i] && (c = map[i][j]); i++) {
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
int check_row_and_col_filled_at_50_per_cent(char **map) {
	char c;
	int found;
	int i, j;

	if (!map) {
		return (0);
	}

	//Check that the row is filled at more than 50%
	for (i = 0; map[i]; i++) {
		found = 0;

		for (j = 0; (c = map[i][j]); j++) {
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
	for (j = 0; map[i] && map[i][j]; j++) {
		found = 0;

		for (i = 0; map[i] && (c = map[i][j]); i++) {
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
int get_next_letter_in_row(char **map, int i, int j) {
	char c = '\0';

	if (map && map[i]) {
		while ((c = map[i][j])) {
			if (c >= 'a' && c <= 'z') {
				break;
			}
			j++;
		}
	}

	return (j);
}

int free_map(char ***map) {
	if (!map || *map) {
		return (-1);
	}

	for (int i = 0; map[0][i]; i++) {
		free(map[0][i]);
	}

	free(*map);
	*map = NULL;
	return (0);
}


char **new_words_list(char **map) {
	char **words = NULL;
	int row_count = 0;
	int col_count = 0;
	int words_count = 0;
	int words_max_len = 0;

	row_count = get_map_row_count(map);
	col_count = get_map_col_count(map);

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

//returns word map
char **get_words(char **map) {
	char **words = NULL;
	char c;
	int i, j;
	int k, l;
	int m, n;

	if (!map) {
		return (NULL);
	}

	if (!(words = new_words_list(map))) {
		return (NULL);
	}

	//Get horizontal words
	i = -1;
	k = -1;
	while (map[++i]) {
		++k;
		l = -1;
		j = -1;
		while (map[i][++j]) {
			j = get_next_letter_in_row(map, i, j);
			if ((c = map[i][j]) != -1) {
				words[k][++l] = c;
			}
		}
		words[k][++l] = '\0';
	}

	//Get vertical words
	i = 0;
	j = -2;
	k -= 1;
	while (map[i] && map[i][(j += 2)]) {
		m = 0;
		n = j;
		l = 0;
		++k;
		while (map[m] && map[m][n]) {
			c = map[m][n];
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
int check_no_duplicated_words(char **map) {
	char **words = NULL;
	int i, j;

	if (!map) {
		return (0);
	}

	if (!(words = get_words(map))) {
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

	free_map(&words);
	return (-1);
}

//returns 0 or failing line in case of failure
int check_row_lenght_not_even(char **map) {
	if (!map) {
		return (0);
	}

	for (int i = 0; map[i]; i++) {
		if (strlen(map[i]) % 2) {
			return (i + 1);
		}
	}

	return (-1);
}

//returns 0 or failing line in case of failure
int check_square_of_2_letter_or_2_empty_blocks(char **map) {
	char c, p;

	if (!map) {
		return (0);
	}

	for (int i = 0; map[i]; i++) {
		for (int j = 0; (c = map[i][j]); j++) {
			if (j % 2 != 0) {
				p = map[i][j - 1];

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
	char **map = NULL;
	unsigned int line_count = 0;

	if (!(cword = getfile(cword_file))) {
		printf("Error: cword: set to NULL");
		return (-1);
	}

	line_count = get_line_count(cword);
	map = set_map(cword, line_count);

	show_map(map);

	printf("Running tests...\n");
	if ((row = check_row_size(map)) >= 0) {
		printf("failed: at row[%d]: row size : make sure every line has the same size\n", row);
	}
	else if ((row = check_row_lenght_not_even(map)) >= 0) {
		printf("failed: at row[%d]: row size not even\n", row);
	}
	else if ((row = check_wrong_character(map)) >= 0) {
		printf("failed: at row[%d]: wrong character: characters must be uncapitalised letters or `%c` \n", row, EMPTY);
	}
	else if ((row = check_square_of_2_letter_or_2_empty_blocks(map)) >= 0) {
		printf("failed: at row[%d]: each square must contain 2 letters or 2 empty blocks \n", row);
	}
	else if ((row = check_at_least_one_blank(map)) >= 0) {
		printf("failed: at row[%d]: each column and row must contain at least one blank\n", row);
	}
	else if ((row = check_row_and_col_filled_at_50_per_cent(map)) >= 0) {
		printf("failed: at row[%d]: each column and row must be filled more than 50 percent \n", row);
	}
	else if ((row = check_no_duplicated_words(map)) >= 0) {
		printf("failed: at row[%d]: no duplicated words \n", row);
	}

	//free memory
	free(cword);
	free(map);

	//failed
	if (row >= 0) {
		exit(EXIT_FAILURE);
	}

	printf("Congratulations your puzzler is valid !!\n");

	return (0);
}

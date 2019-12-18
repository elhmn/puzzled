/* ************************************************************************** */
/*                                                                            */
/*  test_puzzled.c                                                            */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:01:37 2019                        by elhmn        */
/*   Updated: Wed Dec 18 09:40:28 2019                        by bmbarga      */
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

//returns 0 or failing line in case of failure
int check_no_duplicated_row_words(char **map) {
	char c1, c2;
	int i, j;
	int k, l;
	int match;

	if (!map) {
		return (0);
	}

	i = -1;
	while (map[++i]) {
		k = i;
		while (map[++k]) {
			j = -1;
			l = -1;
			match = 1;
			while ((c1 = map[i][++j])) {
				//found letter
				if (c1 >= 'a' && c1 <= 'z') {
					while (map[k][++l]) {
						l = get_next_letter_in_row(map, k, l);
						if ((c2 = map[k][l]) != -1) {
							if (c2 == c1) {
								match *= 1;
							} else {
								match *= 0;
							}
							break;
						}
					}
				}
			}
			if (match) {
				return (i + 1);
			}
		}
	}

	return (-1);
}

//returns 0 or failing line in case of failure
int check_no_duplicated_col_words(char **map) {
	if (!map) {
		return (0);
	}

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
	else if ((row = check_no_duplicated_row_words(map)) >= 0) {
		printf("failed: at row[%d]: no duplicated row words \n", row);
	}
	else if ((row = check_no_duplicated_col_words(map)) >= 0) {
		printf("failed: at row[%d]: no duplicated col words \n", row);
	}

	//free memory
	free(cword);
	free(map);

	//failed
	if (row >= 0) {
		exit(EXIT_FAILURE);
	}

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*  test_puzzled.c                                                            */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:01:37 2019                        by elhmn        */
/*   Updated: Tue Dec 17 02:18:25 2019                        by bmbarga      */
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

	for (int i = 0; cword[i] != '\0'; i++) {
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
	for (int i = 0; map[i] != NULL; i++) {
		printf("[%s]\n", map[i]);
	}
}

int check_row_size(char **map) {
	int len;
	int prevlen;

	if (!map) {
		return (0);
	}

	len = strlen(map[0]);
	prevlen = len;
	for (int i = 1; map[i] != NULL; i++) {
		if (prevlen != (len = strlen(map[i]))) {
			return (0);
		}
	}

	return (1);
}

int check_wrong_character(char **map) {
	char c;

	if (!map) {
		return (0);
	}

	for (int i = 0; map[i] != NULL; i++) {
		for (int j = 0; (c = map[i][j]) != '\0'; j++) {
			if (!((c >= 'a' && c <= 'z') || c == EMPTY)) {
				return (0);
			}
		}
	}

	return (1);
}


int check_at_least_one_blank(char **map) {
	char c;
	int	 found;
	int i, j;

	if (!map) {
		return (0);
	}

	//Check for at list one empty block in a row
	for (i = 0; map[i] != NULL; i++) {
		found = 0;

		for (j = 0; (c = map[i][j]) != '\0'; j++) {
			if (c == EMPTY) {
				found = 1;
			}
		}

		if (!found) {
			return (0);
		}
	}

	//Check for at list one empty block in a column
	i = 0;
	for (j = 0; map[i] != NULL && map[i][j] != '\0'; j++) {
		found = 0;

		for (i = 0; map[i] != NULL && (c = map[i][j]) != '\0'; i++) {
			if (c == EMPTY) {
				found = 1;
			}
		}

		if (!found) {
			return (0);
		}
	}

	return (1);
}


int check_row_and_col_filled_at_50_per_cent(char **map) {
	char c;
	int	 found;
	int i, j;

	if (!map) {
		return (0);
	}

	//Check that the row is filled at more than 50%
	for (i = 0; map[i] != NULL; i++) {
		found = 0;

		for (j = 0; (c = map[i][j]) != '\0'; j++) {
			if (c == EMPTY) {
				found++;
			}
		}

		if (found > j / 2) {
			return (0);
		}
	}

	//Check that the row is filled at more than 50%
	i = 0;
	for (j = 0; map[i] != NULL && map[i][j] != '\0'; j++) {
		found = 0;

		for (i = 0; map[i] != NULL && (c = map[i][j]) != '\0'; i++) {
			if (c == EMPTY) {
				found++;
			}
		}

		if (found > i / 2) {
			return (0);
		}
	}

	return (1);
}

int check_no_duplicated_words(char **map) {
	if (!map) {
		return (0);
	}
	//TODO
	return (1);
}

int check_row_lenght_not_even(char **map) {
	if (!map) {
		return (0);
	}

	for (int i = 0; map[i] != NULL; i++) {
		if (strlen(map[i]) % 2) {
			return (0);
		}
	}

	return (1);
}

int check_square_of_2_letter_or_2_empty_blocks(char **map) {
	char c, p;

	if (!map) {
		return (0);
	}

	for (int i = 0; map[i] != NULL; i++) {
		for (int j = 0; (c = map[i][j]) != '\0'; j++) {
			if (j % 2 != 0) {
				p = map[i][j - 1];

				//If [j - 1] capitalised && [j] !capitalised
				if (p >= 'a' && p <= 'z' && !(c >= 'a' && c <= 'z')) {
					return (0);
				}

				//If [j - 1] empty && [j] !empty
				if (p == EMPTY && c != EMPTY) {
					return (0);
				}
			}
		}
	}
	return (1);
}

int test_puzzled(char *cword_file) {
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
	if (!check_row_size(map)) {
		printf("failed: row size : make sure every line has the same size\n");
	}
	else if (!check_row_lenght_not_even(map)) {
		printf("failed: row size not even\n");
	}
	else if (!check_wrong_character(map)) {
		printf("failed: wrong character: characters must be uncapitalised letters or %c \n", EMPTY);
	}
	else if (!check_square_of_2_letter_or_2_empty_blocks(map)) {
		printf("failed: each square must contain 2 letters or 2 empty blocks \n");
	}
	else if (!check_at_least_one_blank(map)) {
		printf("failed: each column and row must contain at least one blank\n");
	}
	else if (!check_row_and_col_filled_at_50_per_cent(map)) {
		printf("failed: each column and row must be filled more than 50 percent \n");
	}
	else if (!check_no_duplicated_words(map)) {
		printf("failed: no duplicated words \n");
	}

	free(cword);
	free(map);
	return (0);
}

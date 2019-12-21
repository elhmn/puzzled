/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Sat Dec 21 09:12:59 2019                        by bmbarga      */
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

//get map row count
int get_map_row_count(char **map) {
	int n = 0;

	if (!map) {
		return (n);
	}

	for (int i = 0; map[i]; i++) {
		n++;
	}
	return (n);
}

//get map col count
int get_map_col_count(char **map) {
	if (!map) {
		return (0);
	}

	return (strlen(map[0]));
}

int puzzled(int n, int m, char *dict_file) {
	char *dict = NULL;

	printf("puzzled is running with N = [%d] && M = [%d]\n", n, m); // Debug

	if (!(dict = getfile(dict_file))) {
		printf("Error: dict: set to NULL");
		return (-1);
	}

	free(dict);
	return (0);
}

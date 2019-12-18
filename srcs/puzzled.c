/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Wed Dec 18 11:09:16 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

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

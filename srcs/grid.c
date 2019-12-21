/* ************************************************************************** */
/*                                                                            */
/*  grid.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Sat Dec 21 09:19:19 2019                        by elhmn        */
/*   Updated: Sat Dec 21 09:21:38 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **set_grid(char *src, unsigned int size) {
	char **grid = NULL;

	if (!src) {
		return (NULL);
	}

	if (!(grid = (char**)malloc(sizeof(char*) * (size + 1)))) {
		return (NULL);
	}
	*(grid + size) = NULL;

	int i = 0;
	*(grid + i) = strtok(src, "\n");
	while (*(grid + i++)) {
		*(grid + i) = strtok(NULL, "\n");
	}
	return (grid);
}

void show_grid(char** grid) {
	if (!grid) {
		return ;
	}
	for (int i = 0; grid[i]; i++) {
		printf("[%s]\n", grid[i]);
	}
}

int free_grid(char ***grid) {
	if (!grid || !*grid) {
		return (-1);
	}

	for (int i = 0; grid[0][i]; i++) {
		free(grid[0][i]);
	}

	free(*grid);
	*grid = NULL;
	return (0);
}

//get grid row count
int get_grid_row_count(char **grid) {
	int n = 0;

	if (!grid) {
		return (n);
	}

	for (int i = 0; grid[i]; i++) {
		n++;
	}
	return (n);
}

//get grid col count
int get_grid_col_count(char **grid) {
	if (!grid) {
		return (0);
	}

	return (strlen(grid[0]));
}

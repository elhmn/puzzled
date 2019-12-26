/* ************************************************************************** */
/*                                                                            */
/*  grid.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Sat Dec 21 09:19:19 2019                        by elhmn        */
/*   Updated: Thu Dec 26 11:28:58 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grid.h"

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

void sort_grid_size(char **grid) {
	int len;
	int i, j;
	char *jtmp;
	char *swap;

	if (grid) {
		len = get_grid_row_count(grid);
		for (i = 1; i < len; i++) {
			for (j = i; j > 0 && strlen(swap = grid[j - 1]) < strlen(jtmp = grid[j]); j--) {
				grid[j] = swap;
				grid[j - 1] = jtmp;
			}
		}
	}
}

void sort_grid_alphabetic(char **grid) {
	int len;
	int i, j;
	char *jtmp;
	char *swap;

	if (grid) {
		len = get_grid_row_count(grid);
		for (i = 1; i < len; i++) {
			for (j = i; j > 0 && strcmp((swap = grid[j - 1]), (jtmp = grid[j])) > 0; j--) {
				grid[j] = swap;
				grid[j - 1] = jtmp;
			}
		}
	}
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

char **new_grid(int rc, int cc) {
	char **grid;

	if (rc <= 0 && cc <= 0) {
		return (NULL);
	}

	if (!(grid = (char**)malloc(sizeof(char*) * (rc + 1)))) {
		return (NULL);
	}
	grid[rc] = NULL;

	for (int i = 0; i < rc; i++) {
		if (!(grid[i] = (char*)malloc(sizeof(char) * (cc + 1)))) {
			return (NULL);
		}
		grid[i][cc] = '\0';
	}
	return (grid);
}

void fill_grid(char **grid, char c) {
	int rc, cc;

	if (grid) {
		rc = get_grid_row_count(grid);
		cc = get_grid_col_count(grid);
		for (int i = 0; i < rc; i++) {
			for (int j = 0; j < cc; j++) {
				grid[i][j] = c;
			}
		}
	}
}

void fill_grid_row_col(char **grid, int rc, int cc, char c) {
	if (grid) {
		for (int i = 0; i < rc; i++) {
			for (int j = 0; j < cc; j++) {
				grid[i][j] = c;
			}
		}
	}
}

char **new_filled_grid(int rc, int cc, char c) {
	char **grid = NULL;

	if (!(grid = new_grid(rc, cc))) {
		return (NULL);
	}
	fill_grid_row_col(grid, rc, cc, c);
	return (grid);
}

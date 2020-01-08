/* ************************************************************************** */
/*                                                                            */
/*  grid.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Sat Dec 21 09:19:19 2019                        by elhmn        */
/*   Updated: Wed Jan 08 12:35:55 2020                        by bmbarga      */
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

	if (!(grid = (char**)calloc(size + 1, sizeof(char*)))) {
		return (NULL);
	}
	grid[size] = NULL;

	int i = 0;
	grid[i] = strtok(src, "\n");
	while (grid[i++]) {
		grid[i] = strtok(NULL, "\n");
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
		printf("%d-[%s]\n", i, grid[i]);
	}
}

int free_grid(char ***grid) {
	int i = -1;

	if (!grid || !*grid) {
		return (-1);
	}

	while (grid[0][++i]) {
		free(grid[0][i]);
		grid[0][i] = NULL;
	}

	free(grid[0]);
	grid[0] = NULL;
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
	if (!grid || !grid[0]) {
		return (0);
	}

	return (strlen(grid[0]));
}

//returns a 2 dimension grid initialised
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

char **new_grid_uni_dimension(int rc) {
	char **grid;

	if (!(grid = (char**)malloc(sizeof(char*) * (rc + 1)))) {
		return (NULL);
	}
	for (int i = 0; i <= rc; i++) {
		grid[i] = NULL;
	}
	return (grid);
}

char **duplicate_grid_and_keep_col(int rc, char **src) {
	char **grid;

	if (!src) {
		return (NULL);
	}

	if (!(grid = (char**)malloc(sizeof(char*) * (rc + 1)))) {
		return (NULL);
	}
	grid[rc] = NULL;

	for (int i = 0; i < rc; i++) {
		grid[i] = src[i];
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

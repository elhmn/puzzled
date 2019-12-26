/* ************************************************************************** */
/*                                                                            */
/*  bruteforce.c                                                              */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Tue Dec 24 15:44:04 2019                        by elhmn        */
/*   Updated: Thu Dec 26 11:40:06 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "grid.h"
#include "color.h"
#include "puzzled.h"

char **bruteforce(int n, int m, t_dict dict) {
	char	**grid = NULL;
	char	**dwords = NULL;

	if (!(grid = new_filled_grid(n, m * 2, EMPTY))) {
		printf(COLOR_RED
		"failed to initialise new crossword grid\n"
		COLOR_RESET);
		return (NULL);
	}

	dwords = dict.words;
	return (grid);
}

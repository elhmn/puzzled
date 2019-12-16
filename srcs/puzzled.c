/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Mon Dec 16 16:50:51 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

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

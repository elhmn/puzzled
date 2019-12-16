/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Mon Dec 16 14:20:02 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "puzzled.h"

char **get_dictionnary(char *dict_file) {
	printf("get dictionnary"); // Debug
	printf("dict_file : %s\n", dict_file); // Debug
	return (NULL);
}

int puzzled(int n, int m, char *dict_file) {
	printf("puzzled is running with N = [%d] && M = [%d]\n", n, m); // Debug
	get_dictionnary(dict_file);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*  test_puzzled.c                                                            */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:01:37 2019                        by elhmn        */
/*   Updated: Mon Dec 16 16:50:30 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

int test_puzzled(char *cword_file) {
	char *cword = NULL;

	if (!(cword = getfile(cword_file))) {
		printf("Error: cword: set to NULL");
		return (-1);
	}

	printf("%s", cword);
	free(cword);
	return (0);
}

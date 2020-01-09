/* ************************************************************************** */
/*                                                                            */
/*  putfile.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Thu Jan  9 15:55:01 2020                        by elhmn        */
/*   Updated: Thu Jan 09 16:13:05 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

int putfile(char *file, char *str) {
	FILE *fp = NULL;

	if (!str) {
		return (-1);
	}

	if (!(fp = fopen(file, "w"))) {
		perror("Error: fopen: ");
		exit(EXIT_FAILURE);
	}

	//This call is only
	fwrite(str, sizeof(char), strlen(str), fp);

	fclose(fp);
	return (0);
}

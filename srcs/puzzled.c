/* ************************************************************************** */
/*                                                                            */
/*  puzzled.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:16:42 2019                        by elhmn        */
/*   Updated: Mon Dec 16 15:27:51 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "puzzled.h"

char *getfile(char *dict_file) {
	FILE *fp = NULL;
	char *dict = NULL;
	long fsize = 0;

	if (!(fp = fopen(dict_file, "r"))) {
		perror("Error: fopen: ");
		exit(EXIT_FAILURE);
	}

	//Get file size
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//create dict string
	if (!(dict = (char*)malloc(fsize + 1))) {
		return (NULL);
	}

	//This call is only
	fread(dict, 1, fsize, fp);

	fclose(fp);
	return (dict);
}

int puzzled(int n, int m, char *dict_file) {
	char *dict = NULL;

	printf("puzzled is running with N = [%d] && M = [%d]\n", n, m); // Debug

	if (!(dict = getfile(dict_file))) {
		printf("Error: dict: set to NULL");
		return (-1);
	}

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*  getfile.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:05:12 2019                        by elhmn        */
/*   Updated: Mon Dec 16 16:05:13 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <string.h>
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

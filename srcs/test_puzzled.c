/* ************************************************************************** */
/*                                                                            */
/*  test_puzzled.c                                                            */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Mon Dec 16 16:01:37 2019                        by elhmn        */
/*   Updated: Mon Dec 16 18:40:24 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

//This is shit I will fix that later
unsigned int get_line_count(char *cword) {
	unsigned int line_count = 1;

	if (!cword || !strlen(cword) || !strcmp(cword, "\n")) {
		return (0);
	}

	for (int i = 0; cword[i] != '\0'; i++) {
		if (cword[i] == '\n'
				&& cword[i + 1] != '\0'
				&& cword[i + 1] != '\n') {
			line_count++;
		}
	}

	return (line_count);
}

char **set_map(char *src, unsigned int size) {
	char **map = NULL;

	if (!src) {
		return (NULL);
	}

	if (!(map = (char**)malloc(sizeof(char*) * (size + 1)))) {
		return (NULL);
	}
	*(map + size) = NULL;

	int i = 0;
	*(map + i) = strtok(src, "\n");
	while (*(map + i++)) {
		*(map + i) = strtok(NULL, "\n");
	}
	return (map);
}

void show_map(char** map) {
	if (!map) {
		return ;
	}
	for (int i = 0; map[i] != NULL; i++) {
		printf("[%s]\n", map[i]);
	}
}

int test_puzzled(char *cword_file) {
	char *cword = NULL;
	char **map = NULL;
	unsigned int line_count = 0;

	if (!(cword = getfile(cword_file))) {
		printf("Error: cword: set to NULL");
		return (-1);
	}

	printf("cword : {\n%s}\n", cword); // Debug

	line_count = get_line_count(cword);
	map = set_map(cword, line_count);
	show_map(map);

	free(cword);
	free(map);
	return (0);
}

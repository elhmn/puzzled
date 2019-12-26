/* ************************************************************************** */
/*                                                                            */
/*  main.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:03:10 2019                        by elhmn        */
/*   Updated: Sat Dec 21 10:20:17 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "puzzled.h"

int g_quiet = 0;

void print_usage(char *program) {
	printf("Usage:\n%s -M nRows -N nColumns [-d dictionnaryFilePath]\n", program);
	printf("\tWhere M > 0 and N > 0 \n\n");
	printf("-q to disable grid output\n");
	printf("-t [testFilePath] to test crossword:\n");
	printf("\t%s -t [testFilePath]\n", program);
}

int		main(int ac, char** av) {
	char *dict_file = DICTIONNARY;
	char *test_file = NULL;
	int c, m, n = 0;

	//getopt does not display error in case of failure
	opterr = 0;

	while (optind < ac) {
		if ((c = getopt(ac, av, "M:N:d:t:q")) != -1) {
			switch (c) {
				//Should run test puzzled
				case 't' :
					test_file = optarg;
					break;
				case 'q' :
					g_quiet = 1;
					break;
					//Set file name
				case 'd' :
					dict_file = optarg;
					break;
					//Number of columns
				case 'N' :
					n = atoi(optarg);
					break;
					//Number of rows
				case 'M' :
					m = atoi(optarg);
					break;
				case '?' :
					print_usage(av[0]);
					exit(EXIT_FAILURE);
					break;
				default:
					break;
			}
		} else {
			optind++;
		}
	}

	//Run test if -t is specified
	if (test_file) {
		test_puzzled(test_file);
	} else {
		//check flags
		if (m <= 0 || n <= 0) {
			print_usage(av[0]);
			return (EXIT_FAILURE);
		}
		puzzled(m, n, dict_file);
	}

	return (EXIT_SUCCESS);
}

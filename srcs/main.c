/* ************************************************************************** */
/*                                                                            */
/*  main.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:03:10 2019                        by elhmn        */
/*   Updated: Mon Dec 16 16:48:28 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "puzzled.h"

void print_usage(char *program) {
	printf("Usage:\n%s -N nRows -M nColumns [-d dictionnaryFilePath]\n", program);
	printf("\tWhere N > 0 and M > 0 \n");
	printf("\nTo test a crossword Use :\n");
	printf("%s -t [testFilePath]\n", program);
}

int		main(int ac, char** av) {
	char *dict_file = DICTIONNARY;
	char *test_file = NULL;
	int c, n, m = 0;

	//getopt does not display error in case of failure
	opterr = 0;

	while (optind < ac) {
		if ((c = getopt(ac, av, "M:N:d:t:")) != -1) {
			switch (c) {
				//Should run test puzzled
				case 't' :
					test_file = optarg;
					break;
					//Set file name
				case 'd' :
					dict_file = optarg;
					break;
					//Number of rows
				case 'N' :
					n = atoi(optarg);
					break;
					//Number of columns
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
		if (n <= 0 || m <= 0) {
			print_usage(av[0]);
			return (EXIT_FAILURE);
		}
		puzzled(n, m, dict_file);
	}

	return (EXIT_SUCCESS);
}

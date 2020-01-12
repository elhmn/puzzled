/* ************************************************************************** */
/*                                                                            */
/*  main.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:03:10 2019                        by elhmn        */
/*   Updated: Sun Jan 12 17:49:47 2020                        by elhmn        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "puzzled.h"

#ifdef __EMSCRIPTEN__

# include <SDL/SDL.h>
# include <emscripten.h>

#endif //__EMSCRIPTEN__

int g_quiet = 0;
int g_interactive = 0;
int g_output = 0;

#ifdef __EMSCRIPTEN__
unsigned int g_limit = 10;
#else
unsigned int g_limit = 0;
#endif //__EMSCRIPTEN__

void print_usage(char *program) {
	printf("Usage:\n%s -M nRows -N nColumns [-d dictionnaryFilePath]\n", program);
	printf("\tWhere M > 0 and N > 0 \n\n");
	printf("-q to disable grid output can only be coupled with -t\n");
	printf("-i to run in interactive mode\n");
	printf("-l set the maximum amount of grid you would like to generate does not work with -i\n");
	printf("-o generate a file for each puzzler found and stores them in ./generated folder\n");
	printf("-t [testFilePath] to test crossword:\n");
	printf("\t%s -t [testFilePath]\n", program);
}

#ifdef __EMSCRIPTEN__

int main(void) {
	emcc_puzzled(4, 6, DICTIONNARY);
	return (0);
}

#else //NOT __EMSCRIPTEN__

int		main(int ac, char** av) {
	char *dict_file = DICTIONNARY;
	char *test_file = NULL;
	int c, m, n = 0;

	//getopt does not display error in case of failure
	opterr = 0;

	while (optind < ac) {
		if ((c = getopt(ac, av, "M:N:d:t:qil:o")) != -1) {
			switch (c) {
				//Should run test puzzled
				case 't' :
					test_file = optarg;
					break;
				//Should run in interactive mode
				case 'i' :
					g_interactive = 1;
					break;
				case 'o' :
					g_output = 1;
					break;
				case 'l' :
					g_limit = atoi(optarg);
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
#endif

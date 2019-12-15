/* ************************************************************************** */
/*                                                                            */
/*  main.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:03:10 2019                        by elhmn        */
/*   Updated: Sun Dec 15 13:52:50 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "puzzled.h"

int		main(int ac, char** av) {
	char *file = DICTIONNARY;
	int c, n, m = 0;

	//getopt does not display error in case of failure
	opterr = 0;

	while (optind < ac) {
		if ((c = getopt(ac, av, "M:N:f:")) != -1) {
			switch (c) {
				case 'f' :
					file = optarg;
					break;
				case 'N' :
					n = atoi(optarg);
					break;
				case 'M' :
					m = atoi(optarg);
					break;
				default:
					break;
			}
		} else {
			optind++;
		}
	}

	//check flags
	if (n <= 0 || m <= 0) {
		printf("Usage: %s -N nRows -M nColumns [-file dictionnaryFilePath]\n", av[0]);
		printf("\tWhere N > 0 and M > 0 \n");
		return (EXIT_FAILURE);
	}

	puzzled(n, m);
	return (EXIT_SUCCESS);
}

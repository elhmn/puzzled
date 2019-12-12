/* ************************************************************************** */
/*                                                                            */
/*  main.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Dec 11 16:03:10 2019                        by elhmn        */
/*   Updated: Thu Dec 12 10:51:11 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzled.h"

int		main(int ac, char** av)
{
	if (ac != 3)
	{
		printf("Usage: puzzled <M> <N>\n");
		return (-1);
	}
	puzzled(atoi(av[1]), atoi(av[2]));
	return (0);
}

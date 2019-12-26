/* ************************************************************************** */
/*                                                                            */
/*  puzzled.h                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Tue Dec 24 15:49:34 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLED_H
# define PUZZLED_H

#include "dict.h"

#define DICTIONNARY "/usr/share/dict/words"
#define TESTDIR "./tests/"
#define EMPTY '.'

int				puzzled(int m, int n, char *file);
char			*getfile(char *dict_file);
int				test_puzzled(char *file);
unsigned int	get_line_count(char *cword);
char			**bruteforce(int m, int n, t_dict dict);

#endif

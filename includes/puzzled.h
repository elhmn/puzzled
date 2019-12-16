/* ************************************************************************** */
/*                                                                            */
/*  puzzled.h                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Mon Dec 16 16:41:16 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLED_H
# define PUZZLED_H

#define DICTIONNARY "/usr/share/dict/words"
#define TESTDIR "./tests/"

int		puzzled(int n, int m, char *file);
char	*getfile(char *dict_file);
int		test_puzzled(char *file);

#endif

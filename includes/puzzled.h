/* ************************************************************************** */
/*                                                                            */
/*  puzzled.h                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Sat Dec 21 09:18:58 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLED_H
# define PUZZLED_H

#define DICTIONNARY "/usr/share/dict/words"
#define TESTDIR "./tests/"
#define EMPTY '.'

int				puzzled(int n, int m, char *file);
char			*getfile(char *dict_file);
int				test_puzzled(char *file);
unsigned int	get_line_count(char *cword);

#endif

/* ************************************************************************** */
/*                                                                            */
/*  puzzled.h                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Wed Dec 18 11:09:30 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLED_H
# define PUZZLED_H

#define DICTIONNARY "/usr/share/dict/words"
#define TESTDIR "./tests/"
#define EMPTY '.'

int		puzzled(int n, int m, char *file);
char	*getfile(char *dict_file);
int		test_puzzled(char *file);
int		get_map_row_count(char **map);
int		get_map_col_count(char **map);

#endif

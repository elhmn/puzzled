/* ************************************************************************** */
/*                                                                            */
/*  puzzled.h                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Sun Jan 05 17:31:33 2020                        by bmbarga      */
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
int				check_at_least_one_blank(char **grid);
int				check_row_and_col_filled_at_50_per_cent(char **grid);
int 			check_no_duplicated_words(char **grid);
int				check_words_belong_to_dictionnary(char **grid, t_dict dict);
char			**get_words(char **grid);
char			**get_vertical_words(char **grid);

#endif

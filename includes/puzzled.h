/* ************************************************************************** */
/*                                                                            */
/*  puzzled.h                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Thu Jan 09 16:15:13 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLED_H
# define PUZZLED_H

#include "dict.h"

#define DICTIONNARY "/usr/share/dict/words"
#define TESTDIR "./tests/"
#define GENERATED_CW_FOLDER "./gen/"
#define EMPTY '.'

//MACROS
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

int				puzzled(int m, int n, char *file);
char			*getfile(char *dict_file);
int				putfile(char *dict_file, char *str);
int				test_puzzled(char *file);
unsigned int	get_line_count(char *cword);
char			**bruteforce(int m, int n, t_dict dict);
int				check_at_least_one_blank(char **grid);
int				check_at_least_one_blank_rc_cc(char **grid, int rc, int cc);
int				check_row_and_col_filled_at_50_per_cent(char **grid);
int				check_row_and_col_filled_at_50_per_cent_rc_cc(char **grid, int rc, int cc);
int 			check_no_duplicated_words(char **grid);
int				check_no_duplicated_words_rc_cc(char **grid, int rc, int cc);
int				check_words_belong_to_dictionnary(char **grid, t_dict dict, int rc, int cc);
char			**get_words(char **grid);
char			**get_vertical_words(char **grid, int rc, int cc);

#endif

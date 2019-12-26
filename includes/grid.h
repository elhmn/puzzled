/* ************************************************************************** */
/*                                                                            */
/*  grid.h                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Sat Dec 21 09:22:14 2019                        by elhmn        */
/*   Updated: Thu Dec 26 11:24:17 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

int				get_grid_row_count(char **grid);
int				get_grid_col_count(char **grid);
char			**set_grid(char *src, unsigned int size);
int				free_grid(char ***grid);
void			show_grid(char** grid);
void			sort_grid_size(char **grid);
void			sort_grid_alphabetic(char **grid);
char			**new_grid(int rc, int cc);
char			**new_filled_grid(int rc, int cc, char c);
void			fill_grid(char **grid, char c);
void			fill_grid_row_col(char **grid, int rc, int cc, char c);

#endif

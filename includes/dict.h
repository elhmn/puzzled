/* ************************************************************************** */
/*                                                                            */
/*  dict.h                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Tue Dec 24 15:13:32 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

typedef struct	s_dict {
	int		maxlen; //lenght of the longest word in the dictionnary
	int		wcount; //word count
	int		ceven; //words that are even
	char	**words;
}				t_dict;

int init_dict(int n, int m, char **words, int line_count, t_dict *dict);
void dump_dict(t_dict *dict);
int free_dict(t_dict *dict);

#endif

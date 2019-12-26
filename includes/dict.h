/* ************************************************************************** */
/*                                                                            */
/*  dict.h                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Thu Dec 26 14:41:42 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

typedef struct	s_dict {
	int		maxlen; //lenght of the longest word in the dictionnary
	int		minlen; //lenght of the shortest word in the dictionnary
	int		wcount; //word count
	int		ceven; //words that are even
	char	**words;
}				t_dict;

int init_dict(int n, int m, char **words, int line_count, t_dict *dict);
void dump_dict(t_dict dict);
int free_dict(t_dict *dict);

#endif

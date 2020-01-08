/* ************************************************************************** */
/*                                                                            */
/*  dict.h                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created:                                                 by elhmn        */
/*   Updated: Wed Jan 08 17:45:06 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include "libft.h"

# define INDEX_SIZE 26
# define HASHTABLE_SIZE 10000

typedef struct	s_dict {
	int		maxlen; //lenght of the longest word in the dictionnary
	int		minlen; //lenght of the shortest word in the dictionnary
	int		wcount; //word count
	int		ceven; //words that are even
	char	**words;
	char	***comb; //list of word combinations
	int		*comb_count; //list of word combinations
	int		*placed_w; //list of word combinations
	int		index[INDEX_SIZE]; //dictionnary alphabetic index
	t_hash	*hash; //hash table that contains every ordered of cell valid in a dictionnary
}				t_dict;

int init_dict(int m, int n, char **words, int line_count, t_dict *dict);
void dump_dict(t_dict dict);
int free_dict(t_dict *dict);
int search_word(t_dict *dict, char *word);
int get_end_index(t_dict *dict, char *word);
int get_start_index(t_dict *dict, char *word);

//combinations
void free_comb(char ****comb);
char ***new_word_combination_list(t_dict dict);
void dump_combinations(char ***comb);

#endif

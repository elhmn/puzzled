/* ************************************************************************** */
/*                                                                            */
/*  dict.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Tue Dec 24 14:12:36 2019                        by elhmn        */
/*   Updated: Thu Jan 09 12:26:04 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "libft.h"
#include "grid.h"

void dump_dict(t_dict dict) {
	printf("dict {\n");
	printf("\tdict->ceven:  %d\n", dict.ceven);
	printf("\tdict->wcount: %d\n", dict.wcount);
	printf("\tdict->maxlen: %d\n", dict.maxlen);
	printf("\tdict->minlen: %d\n", dict.minlen);
	printf("\tdict->index: {\n");
	for (int i = 0; i < INDEX_SIZE; i++) {
		if (dict.index[i] >= 0) {
			printf("\t\t%c:%d:[%s]", (i + (int)'a'), dict.index[i], dict.words[dict.index[i]]);
		} else {
			printf("\t\t%c:%d:[(null)]", (i + (int)'a'), dict.index[i]);
		}
		if (i != INDEX_SIZE - 1) {
			printf(",\n");
		}
	}
	printf("\n\t}\n");

	printf("}\n");
}

void dump_combinations(char ***comb) {
	if (comb) {
		for (int i = 0; comb[i]; i++) {
			printf("combinations[%d]\n", i);
			show_grid(comb[i]);
			printf("----\n");
		}
	}
}

int free_dict(t_dict *dict) {
	if (!dict) {
		return (-1);
	}

	free(dict->words);
	free_comb(&dict->comb);
	free(dict->placed_w);

	return (0);
}

int has_valid_char(char *word) {
	int len;
	char c;

	if (!word) {
		return (-1);
	}

	len = strlen(word);
	for (int i = 0; i < len; i++) {
		c = word[i];
		if (!((c >= 'a' && c <= 'z')
					|| (c >= 'A' && c <= 'Z'))) {
			return (-1);
		}
	}

	return (0);
}

int to_lower(char *word) {
	int len;
	char c;

	if (!word) {
		return (-1);
	}

	len = strlen(word);
	for (int i = 0; i < len; i++) {
		c = word[i];
		if (c >= 'A' && c <= 'Z') {
			word[i] = word[i] + 32;
		}
	}

	return (0);
}

int get_start_index(t_dict *dict, char *word) {
	if (dict && word) {
		return (dict->index[word[0] % 'a']);
	}

	return (-1);
}

int get_end_index(t_dict *dict, char *word) {
	int i;

	if (dict && word) {
		i = word[0] % 'a';
		while (++i < INDEX_SIZE) {
			if (dict->index[i] >= 0) {
				return (dict->index[i]);
			}
		}
		return (dict->wcount);
	}

	return (-1);
}

int search_word(t_dict *dict, char *word) {
	int idx_start;
	int	idx_end;

	if (dict && word) {
		if ((idx_start = get_start_index(dict, word)) < 0) {
			return (-1);
		}
		if ((idx_end = get_end_index(dict, word)) < 0) {
			return (-1);
		}

		for (int i = idx_start; i < idx_end; i++) {
			if (!strcmp(dict->words[i], word)) {
				return (i);
			}
		}
	}
	return (-1);
}

int search_word_hash(t_hash *hash, char *word) {
	t_list *l;
	char *str;

	if (hash && word) {
		l = ft_hash_get_node(hash, (unsigned char*)word);

		if (!l) {
			return (-1);
		}

		while (l) {
			str = (char*)l->content;
			if (!strcmp(str, word)) {
				return (0);
			}
			l = l->next;
		}
	}
	return (-1);
}

char **new_dict_word_list(t_dict dict, char **words) {
	char **new_words = NULL;

	if (!words) {
		return (NULL);
	}

	if (!(new_words = (char**)calloc(dict.wcount + 1, sizeof(char*)))) {
		return (NULL);
	}

	return (new_words);
}

char **get_new_dict_words(int m, int n, t_dict dict, char **words, int line_count) {
	char **new_words = NULL;
	char *s = NULL;
	int len = 0;
	int j = 0;

	if (!words) {
		return (NULL);
	}

	if (!(new_words = new_dict_word_list(dict, words))) {
		return (NULL);
	}
	for (int i = 0; i < line_count; i++) {
		s = words[i];
		if (!((len = strlen(s)) % 2)) {
			if (len > 2) {
				//get words than char belongs to [a-z] or [A-Z]
				if (has_valid_char(s) != -1) {
					to_lower(s);
					//get words that can fit in the grid whose size is : len(w) >= max(m - 1, n - 1) * 2
					if (len <= (((m > n ? m : n) - 1) * 2)) {
						if (j >= dict.wcount) {
							break;
						}
						new_words[j++] = s;
					}
				}
			}
		}
	}

	return (new_words);
}

void init_index(t_dict *dict) {
	int wcount;

	if (dict) {
		wcount = dict->wcount;
		for (int i = 0; i < INDEX_SIZE; i++) {
			dict->index[i] = -1;
		}

		for (int i = 0; i < wcount && dict->index[25] == -1; i++) {
			if (dict->words[i] && dict->index[dict->words[i][0] % 'a'] == -1) {
				dict->index[dict->words[i][0] % 'a'] = i;
			}
		}
	}
}

t_hash *get_new_dict_hash(t_dict dict) {
	t_hash *h;
	int wcount;

	if (!(h = ft_new_hash_table(MAX_HASHTABLE_SIZE))) {
		return (NULL);
	}
	wcount = dict.wcount;
	for (int i = 0; i < wcount; i++) {
		ft_hash_insert(h, (unsigned char*)dict.words[i], dict.words[i], 0);
	}
	return (h);
}

t_hash *get_new_col_hash(t_dict dict) {
	t_hash *h;
	int wcount;
	char *word;
	char *tmp;
	int wlen;

	if (!(h = ft_new_hash_table(MAX_HASHTABLE_SIZE))) {
		return (NULL);
	}
	wcount = dict.wcount;
	for (int i = 0; i < wcount; i++) {
		word = dict.words[i];
		wlen = strlen(word);
		for (int j = 0; j < wlen; j += 2) {
			tmp = strndup(word, j + 2);
			if (ft_hash_insert_without_duplicate(h, (unsigned char*)tmp, tmp, 0) < 0) {
				free(tmp);
			}
		}
	}
	return (h);
}


void	dump_hash(t_hash *h) {
	t_list **t;
	int size;
	t_list *l;
	char *str;

	if (!h) {
		return ;
	}

	t = h->table;
	size = h->size;
	printf("size = %d\n", size);
	for (int i = 0; i < size; i++) {
		l = t[i];

		if (!l) {
			continue;
		}

		printf("t[%d] => {\n", i);
		while (l) {
			str = (char*)l->content;
			if (str) {
				printf("\t%s\n", str);
			}
			l = l->next;
		}
		printf("}\n");
	}
}

int init_dict(int m, int n, char **words, int line_count, t_dict *dict) {
	int len;
	int maxlen = 0;
	int minlen = -1;
	int wcount = 0;
	int ceven = 0;
	char *s;

	if (!words) {
		return (-1);
	}

	if (!dict) {
		return (-1);
	}

	for (int i = 0; i < line_count; i++) {
		s = words[i];
		if (!((len = strlen(s)) % 2)) {
			ceven++;
			if (len > 2) {
				//get words than char belongs to [a-z] or [A-Z]
				if (has_valid_char(s) != -1) {
					//get words that can fit in the grid whose size is : len(w) >= max(m - 1, n - 1) * 2
					if (len <= (((m > n ? m : n) - 1) * 2)) {
						wcount++;
						maxlen = maxlen < len ? len : maxlen;
						minlen = minlen > len || minlen < 0 ? len : minlen;
					}

				}
			}
		}
	}

	dict->ceven = ceven;
	dict->wcount = wcount;
	dict->maxlen = maxlen;
	dict->minlen = minlen;

	dict->words = get_new_dict_words(m, n, *dict, words, line_count);
	sort_grid_alphabetic(dict->words);
	init_index(dict);

	dict->comb = new_word_combination_list(*dict);
	if (!(dict->comb_count = (int*)calloc(dict->wcount, sizeof(int)))) {
		return (-1);
	}

	if (!(dict->placed_w = (int*)calloc(m, sizeof(int)))) {
		return (-1);
	}
	for (int i = 0; i < m; i++) {
		dict->placed_w[i] = -1;
	}

	dict->d_hash = get_new_dict_hash(*dict);
	dict->col_hash = get_new_col_hash(*dict);
	return (0);
}

char ***new_word_combination_list(t_dict dict) {
	char ***comb = NULL;

	if (!(comb = (char***)calloc(dict.wcount + 1, sizeof(char**)))) {
		return (NULL);
	}
	return (comb);
}

void free_comb(char ****comb) {
	if (comb && *comb) {
		for (int i = 0; comb[0][i]; i++) {
			if (comb[0][i] != NULL) {
				free_grid(*comb + i);
			}
		}
	}

	free(*comb);
	*comb = NULL;
}

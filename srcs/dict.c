/* ************************************************************************** */
/*                                                                            */
/*  dict.c                                                                    */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Tue Dec 24 14:12:36 2019                        by elhmn        */
/*   Updated: Wed Dec 25 11:11:43 2019                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "grid.h"

void dump_dict(t_dict dict) {
	printf("dict {\n");
	printf("\tdict->ceven:  %d\n", dict.ceven);
	printf("\tdict->wcount: %d\n", dict.wcount);
	printf("\tdict->maxlen: %d\n", dict.maxlen);
	printf("}\n");
}

int free_dict(t_dict *dict) {
	if (!dict) {
		return (-1);
	}

	free(dict->words);

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


char **new_dict_word_list(t_dict dict, char **words) {
	char **new_words = NULL;

	if (!words) {
		return (NULL);
	}

	if (!(new_words = (char**)malloc(sizeof(char*) * (dict.wcount + 1)))) {
		return (NULL);
	}
	new_words[dict.wcount] = NULL;

	return (new_words);
}

char **get_new_dict_words(int n, int m, t_dict dict, char **words, int line_count) {
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
					if (len < ((n > m ? n : m) * 2)) {
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

int init_dict(int n, int m, char **words, int line_count, t_dict *dict) {
	int len;
	int maxlen = 0;
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
					if (len < ((n > m ? n : m) * 2)) {
						wcount++;
						maxlen = maxlen < len ? len : maxlen;
					}

				}
			}
		}
	}

	dict->ceven = ceven;
	dict->wcount = wcount;
	dict->maxlen = maxlen;
	dict->words = get_new_dict_words(n, m, *dict, words, line_count);
	return (0);
}

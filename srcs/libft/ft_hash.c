/* ************************************************************************** */
/*                                                                            */
/*  ft_hash.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 17:29:49 2020                        by elhmn        */
/*   Updated: Fri Jan 10 00:50:28 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dict.h"
#include <stdlib.h>
#include <stdio.h>

t_hash		*ft_new_hash_table(size_t size) {
	t_hash *hash;

	if (!(hash = (t_hash*)malloc(sizeof(t_hash)))) {
		return (NULL);
	}

	hash->size = size;
	if (!(hash->table = (t_list**)calloc(size, sizeof(t_list*)))) {
		return (NULL);
	}
	return (hash);
}

//djb2 hash function
unsigned long ft_hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

	if (!str) {
		return (0);
	}

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void	ft_hash_insert(t_hash *h, unsigned char *str, void const *content, int size) {
	t_list *list = NULL;
	int key = -1;

	if (!h) {
		return ;
	}
	if (!str) {
		return ;
	}

	if (h->table) {
		key = ft_hash(str) % (unsigned long)h->size;
		list = h->table[key];
		if (!list) {
			h->table[key] = ft_lstnew(content, size);
		} else {
			ft_lstadd_end(&list, ft_lstnew(content, size));
		}
	}
}

int	ft_hash_insert_without_duplicate(t_hash *h, unsigned char *str, void const *content, int size) {
	t_list *list = NULL;
	t_list *list_tmp;
	char *content_str;

	int key;

	if (!h) {
		return (-1);
	}
	if (!str) {
		return (-1);
	}

	if (h->table) {
		key = ft_hash(str) % (unsigned long)h->size;
		list = h->table[key];

		if (!list) {
			h->table[key] = ft_lstnew(content, size);
		} else {
			list_tmp = list;

			if (list)
			{
				while (list_tmp->next) {
					if ((content_str = (char*)list_tmp->content) && !strcmp(content_str, (char*)str)) {
						return (-1);
					}
					list_tmp = list_tmp->next;
				}
				if ((content_str = (char*)list_tmp->content) && !strcmp(content_str, (char*)str)) {
					return (-1);
				}
				h->table[key] = list_tmp;
				(list)->next = ft_lstnew(content, size);
			}
		}
	}
	return (0);
}

int	ft_hash_insert_cell_without_duplicate(t_hash *h, unsigned char *str, void const *content, int size) {
	t_list *list = NULL;
	t_list *list_tmp;
	t_cell *cell;

	int key;

	if (!h) {
		return (-1);
	}
	if (!str) {
		return (-1);
	}

	if (h->table) {
		key = ft_hash(str) % (unsigned long)h->size;
		list = h->table[key];

		if (!list) {
			h->table[key] = ft_lstnew(content, size);
		} else {
			list_tmp = list;

			if (list)
			{
				while (list_tmp->next) {
					if ((cell = (t_cell*)list_tmp->content) && cell && !strcmp(cell->cell, (char*)str)) {
						return (-1);
					}
					list_tmp = list_tmp->next;
				}
				if ((cell = (t_cell*)list_tmp->content) && cell && !strcmp(cell->cell, (char*)str)) {
					return (-1);
				}
				h->table[key] = list_tmp;
				(list)->next = ft_lstnew(content, size);
			}
		}
	}
	return (0);
}

t_list *ft_hash_get_node(t_hash *h, unsigned char *str) {
	int key;

	if (!h) {
		return (NULL);
	}

	if (!str) {
		return (NULL);
	}

	if (!(h->table)) {
		return (NULL);
	}
	key = ft_hash(str) % (unsigned long)h->size;
	return (h->table[key]);
}

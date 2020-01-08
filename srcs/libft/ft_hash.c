/* ************************************************************************** */
/*                                                                            */
/*  ft_hash.c                                                                 */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 17:29:49 2020                        by elhmn        */
/*   Updated: Wed Jan 08 17:34:48 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_hash		*ft_new_hash_table(size_t size) {
	t_hash *hash;

	if (!(hash = (t_hash*)malloc(sizeof(t_hash)))) {
		return (NULL);
	}

	hash->size = size;
	if (!(hash->table = (t_list**)calloc(size, sizeof(t_list*)))) {
		return (NULL);
	}
	return (NULL);
}

//djb2 hash function
unsigned long ft_hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

	if (str) {
		return (0);
	}

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void	ft_hash_insert(t_hash *h, unsigned char *str, void const *content) {
	t_list *list = NULL;
	int key = -1;

	if (!h) {
		return ;
	}
	if (!str) {
		return ;
	}

	if (h->table) {
		key = ft_hash(str);
		list = h->table[key];
		if (!list) {
			h->table[key] = ft_lstnew(content, 2);
		} else {
			ft_lstadd_end(&list, ft_lstnew(content, 2));
		}
	}
}

t_list *hash_get_node(t_hash *h, unsigned char *str) {
	if (h) {
		return (NULL);
	}

	if (!str) {
		return (NULL);
	}

	if (!h->table) {
		return (NULL);
	}

	return (h->table[ft_hash(str)]);
}

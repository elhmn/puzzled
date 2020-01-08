/* ************************************************************************** */
/*                                                                            */
/*  ft_lstnew.c                                                               */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:08:31 2020                        by elhmn        */
/*   Updated: Wed Jan 08 16:09:04 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	if (content)
	{
		new->content = malloc(content_size);
		if (!new->content)
			return (0);
		new->content_size = content_size;
		memcpy(new->content, content, content_size);
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}

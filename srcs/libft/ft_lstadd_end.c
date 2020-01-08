/* ************************************************************************** */
/*                                                                            */
/*  ft_lstadd_end.c                                                           */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:10:40 2020                        by elhmn        */
/*   Updated: Wed Jan 08 16:10:45 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list *list_tmp;

	list_tmp = *alst;
	if (*alst)
	{
		while (list_tmp->next)
			list_tmp = list_tmp->next;
		alst = &list_tmp;
		(*alst)->next = new;
	}
}

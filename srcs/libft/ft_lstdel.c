/* ************************************************************************** */
/*                                                                            */
/*  ft_lstdel.c                                                               */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:10:36 2020                        by elhmn        */
/*   Updated: Wed Jan 08 16:10:37 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void*, size_t))
{
	if (alst && *alst && del)
	{
		if ((*alst)->next == NULL)
			ft_lstdelone(alst, del);
		else
		{
			ft_lstdel(&(*alst)->next, del);
			ft_lstdelone(alst, del);
		}
	}
}

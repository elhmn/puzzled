/* ************************************************************************** */
/*                                                                            */
/*  ft_lstadd.c                                                               */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:10:54 2020                        by elhmn        */
/*   Updated: Wed Jan 08 16:11:56 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		(*alst) = new;
	}
}

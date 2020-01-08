/* ************************************************************************** */
/*                                                                            */
/*  ft_lstiter.c                                                              */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:09:47 2020                        by elhmn        */
/*   Updated: Wed Jan 08 16:09:52 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f) (t_list *elem))
{
	if (lst && f)
	{
		if (lst->next == NULL)
			f(lst);
		else
		{
			f(lst);
			ft_lstiter(lst->next, f);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*  libft.h                                                                   */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:07:33 2020                        by elhmn        */
/*   Updated: Wed Jan 08 17:43:58 2020                        by bmbarga      */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;

}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdel(t_list **alst, void (*del) (void*, size_t));
void				ft_lstdelone(t_list **alst, void (*del) (void*, size_t));
void				ft_lstiter(t_list *lst, void (*f) (t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstadd_end(t_list **alst, t_list *new);
t_list				*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem));

#endif

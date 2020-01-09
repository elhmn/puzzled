/* ************************************************************************** */
/*                                                                            */
/*  libft.h                                                                   */
/*                                                                            */
/*   By: elhmn <www.elhmn.com>                                                */
/*             <nleme@live.fr>                                                */
/*                                                                            */
/*   Created: Wed Jan  8 16:07:33 2020                        by elhmn        */
/*   Updated: Thu Jan 09 10:39:46 2020                        by bmbarga      */
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

//very basic hash table
typedef struct		s_hash
{
	t_list			**table;
	size_t			size;
}					t_hash;

t_hash				*ft_new_hash_table(size_t size);
t_list 				*ft_hash_get_node(t_hash *h, unsigned char *str);
void				ft_hash_insert(t_hash *h, unsigned char *str, void const *content, int size);
int				ft_hash_insert_without_duplicate(t_hash *h, unsigned char *str, void const *content, int size);

#endif

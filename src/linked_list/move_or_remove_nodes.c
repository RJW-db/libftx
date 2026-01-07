/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_or_remove_nodes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:45 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/08 17:44:16 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*back;

	if (*lst)
	{
		back = ft_lstlast(*lst);
		back->next = new;
	}
	else
		*lst = new;
}

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstclear(t_lst **lst, void (*del)(void*))
{
	t_lst	*temp;

	if (*lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
		*lst = NULL;
	}
}

void	ft_lstdelone(t_lst *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

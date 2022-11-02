/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:25:44 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/19 00:58:52 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*lst_tmp;
	void			*f_contents;
	t_list			*content_list;
	t_list			*new;

	lst_tmp = lst;
	content_list = NULL;
	new = NULL;
	while (lst_tmp)
	{
		f_contents = (*f)(lst_tmp->content);
		if (f_contents)
		{
			new = ft_lstnew(f_contents);
			ft_lstadd_back(&content_list, new);
			lst_tmp = lst_tmp->next;
		}
		else
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
	}
	return (content_list);
}

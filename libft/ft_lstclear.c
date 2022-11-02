/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:17:06 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/19 00:02:33 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_list;

	if (*lst && del)
	{
		while (*lst)
		{
			del((*lst)->content);
			tmp_list = *lst;
			*lst = (*lst)->next;
			free(tmp_list);
		}
		*lst = 0;
	}
}

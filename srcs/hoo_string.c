/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hoo_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:50 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 08:52:03 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hoo_string(t_node *node, t_global *global, t_p_mom *p_mom)
{
	char	*tmp;
	t_node	*tmp_node;

	if (node->prev && node->prev->token == string)
	{
		tmp = ft_strjoin2(node->prev->str, node->str);
		free(node->str);
		node->str = tmp;
		tmp_node = node->prev->prev;
		if (node->prev == global->head)
			global->head = global->head->next;
		if (node->prev == p_mom->head)
			p_mom->head = p_mom->head->next;
		free(node->prev);
		node->prev = tmp_node;
		if (node->prev)
			node->prev->next = node;
	}
}

void	hoo_space_check(t_p_mom *p_mom)
{
	t_node	*node;
	t_node	*tmp;

	node = p_mom->head;
	while (node && node != p_mom->tail->next)
	{
		if (node->token == space)
		{
			tmp = node->next;
			tmp->prev = node->prev;
			tmp->prev->next = tmp;
			if (node == p_mom->head)
				p_mom->head = tmp;
			free(node->str);
			free(node);
			node = tmp;
		}
		if (node)
			node = node->next;
	}
}

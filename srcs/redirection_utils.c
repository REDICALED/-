/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 05:37:20 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_redirection_util(t_global *global, t_node *node, t_node *tmp)
{
	if (node == global->head && node->next == global->tail)
	{
		global->head = NULL;
		global->tail = NULL;
	}
	else if (node == global->head)
	{
		global->head = tmp;
		tmp->prev = NULL;
	}
	else if (node->next == global->tail)
	{
		global->tail = node->prev;
		global->tail->next = NULL;
	}
	else
	{
		tmp->prev = node->prev;
		node->prev->next = tmp;
	}
}

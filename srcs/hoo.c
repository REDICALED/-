/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hoo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:00 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/17 17:00:26 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_mom_init(t_global *global)
{
	int		i;
	t_node	*node;

	i = -1;
	node = global->head;
	while (++i <= global->p_count)
	{
		global->p_arr[i].i = i;
		global->p_arr[i].input = -1;
		global->p_arr[i].output = -1;
		global->p_arr[i].read_error = 0;
		global->p_arr[i].head = node;
		while (node && node->next && node->token != e_pipe)
			node = node->next;
		global->p_arr[i].tail = node;
		if (node)
			node = node->next;
	}
}

static void	hoo_init(t_global *global)
{
	t_node	*tmp;

	tmp = global->head;
	global->head = global->head->next;
	free(tmp);
	global->head->prev = NULL;
	global->p_arr = (t_p_mom *)malloc(sizeof(t_p_mom) * (global->p_count + 1));
	pipe_mom_init(global);
}

static void	hoo_etc(t_node *node)
{
	if (node->next == NULL || (node->next->token == space && \
		node->next->next == NULL))
		node->token = e_error;
	else
	{
		if (node->token == e_pipe && node->next->token == space && \
				node->next->next == NULL)
		{
			node->token = e_error;
			return ;
		}
		else if (node->next->token == space && node->token != e_pipe)
		{
			node->next = node->next->next;
			free(node->next->prev->str);
			free(node->next->prev);
			node->next->prev = node;
		}
		node = node->next;
		if (node->prev->token == e_pipe && node->token == e_pipe)
			node->prev->token = e_error;
		else if (node->prev->token != e_pipe && node->token >= read_in \
			&& node->token <= e_pipe)
			node->prev->token = e_error;
	}
}

static int	hoo_loop(t_p_mom *p_mom, t_global *global)
{
	t_node	*node;

	node = p_mom->head;
	while (node && node != p_mom->tail->next)
	{
		if (node->token == read_in2)
			hoo_here_doc(node, p_mom->i);
		if (node->token == dollar)
			hoo_dollar(node, global);
		if (node->token == s_quote)
			node->token = string;
		if (node->token == d_quote)
			hoo_double_quote(node, global);
		if (node->token == string)
			hoo_string(node, global, p_mom);
		if (node->token >= read_in && node->token <= e_pipe)
			hoo_etc(node);
		if (node->token == e_error)
		{
			g_exit_code = 258;
			return (1);
		}
		node = node->next;
	}
	return (0);
}

int	hoo(t_global *global)
{
	int	i;
	int	error;

	hoo_init(global);
	i = -1;
	error = 0;
	while (++i <= global->p_count && global->p_arr[i].head)
	{
		if (hoo_loop(&(global->p_arr[i]), global))
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			error = 1;
			break ;
		}
	}
	i = -1;
	while (++i <= global->p_count && global->p_arr[i].head)
		hoo_space_check(&(global->p_arr[i]));
	if (error == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:23 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 17:48:26 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input_loop(t_node *node, t_p_mom *p_mom)
{
	int	fd;

	fd = -1;
	if (p_mom->input != -1)
		close(p_mom->input);
	fd = open(node->next->str, O_RDONLY);
	if (fd == -1)
	{
		close(p_mom->input);
		if (p_mom->output != -1)
			close(p_mom->output);
		p_mom->input = -1;
		p_mom->output = -1;
		p_mom->read_error = 1;
		return ;
	}
	p_mom->input = fd;
}

static void	output_loop(t_node *node, t_p_mom *p_mom)
{
	int		fd;

	fd = -1;
	if (p_mom->output != -1)
		close(p_mom->output);
	if (node->token == read_out)
		fd = open(node->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token == read_out2)
		fd = open(node->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (p_mom->input != -1)
			close(p_mom->input);
		close(p_mom->output);
		p_mom->input = -1;
		p_mom->output = -1;
		p_mom->read_error = 1;
		return ;
	}
	p_mom->output = fd;
}

static void	remove_redirection(t_global *global)
{
	t_node	*node;
	t_node	*tmp;

	node = global->head;
	while (node && node != global->tail)
	{
		if (node && node->token >= read_in && node->token <= read_out2)
		{
			tmp = node->next->next;
			remove_redirection_util(global, node, tmp);
			free(node->next->str);
			free(node->next);
			free(node->str);
			free(node);
			node = tmp;
		}
		else
			node = node->next;
	}
}

static void	set_redirection(t_global *global)
{
	int		i;
	t_node	*node;

	i = 0;
	node = global->head;
	global->p_arr[0].head = global->head;
	global->p_arr[global->p_count].tail = global->tail;
	while (node != global->tail)
	{
		if (node->token == e_pipe)
		{
			global->p_arr[i].tail = node;
			global->p_arr[++i].head = node->next;
		}
		node = node->next;
	}
}

void	redirection(t_global *global)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i <= global->p_count)
	{
		node = global->p_arr[i].head;
		while (node && node != global->p_arr[i].tail->next)
		{
			if (node->token == read_in)
				input_loop(node, &(global->p_arr[i]));
			if (node->token == read_out || node->token == read_out2)
				output_loop(node, &(global->p_arr[i]));
			if (global->p_arr[i].read_error == 1)
			{
				g_exit_code = 1;
				break ;
			}
			node = node->next;
		}
	}
	remove_redirection(global);
	set_redirection(global);
}

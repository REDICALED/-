/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:56 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 16:31:09 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_1(t_global *global, int i)
{
	if (global->line[i] == 0)
		return (1);
	return (0);
}

int	count_2(t_global *global, int i)
{
	if (i >= 1 && (global->line[i - 1] == '<' || global->line[i - 1] == '>') \
		&& global->tail->token != read_in2 && global->tail->token != read_out2)
	{
		if (global->line[i - 1] == '<' && global->line[i] == '<')
		{
			global->tail->token = read_in2;
			global->tail->str = ft_strjoin(global->tail->str, '<');
			return (1);
		}
		else if (global->line[i - 1] == '>' && global->line[i] == '>')
		{
			global->tail->token = read_out2;
			global->tail->str = ft_strjoin(global->tail->str, '>');
			return (1);
		}
	}
	return (0);
}

static int	count_4_check(t_global *global, int *i)
{
	int	j;

	j = 0;
	while (42)
	{
		++j;
		if (global->line[j + (*i)] == 0)
		{
			add_node(global, e_error, global->line[(*i)]);
			(*i) = (*i) + j;
			return (1);
		}
		if (global->line[j + (*i)] == global->line[(*i)])
			break ;
	}
	return (0);
}

int	count_4(t_global *global, int *i)
{
	if (global->line[*i] == '\'')
	{
		if (count_4_check(global, i) == 1)
			return (1);
		add_node(global, s_quote, 0);
		while (global->line[++(*i)] != '\'')
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
		(*i)++;
		return (1);
	}
	else if (global->line[*i] == '\"')
	{
		if (count_4_check(global, i) == 1)
			return (1);
		add_node(global, d_quote, 0);
		while (global->line[++(*i)] != '\"')
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

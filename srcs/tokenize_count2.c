/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_count2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:10 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 05:36:10 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_5(t_global *global, int *i)
{
	int	flag;

	flag = 0;
	if (global->line[*i] == '$')
	{
		add_node(global, dollar, '$');
		(*i)++;
		if (global->line[*i] == '?')
		{
			global->tail->str = ft_strjoin(global->tail->str, \
											global->line[(*i)++]);
			return (1);
		}
		while (ft_isalnum(global->line[*i]) != 0 || global->line[*i] == '_')
		{
			global->tail->str = ft_strjoin(global->tail->str, \
											global->line[(*i)++]);
			flag = 1;
		}
		if (flag == 0 && (ft_strchr("\'<>\" |'\0'", global->line[*i]) == NULL))
			global->tail->str = ft_strjoin(global->tail->str, \
											global->line[(*i)++]);
		return (1);
	}
	return (0);
}

int	count_6(t_global *global, int i)
{
	if (global->line[i] == '<' || global->line[i] == '>' || \
			global->line[i] == '|')
	{
		if (global->line[i] == '<')
			add_node(global, read_in, '<');
		if (global->line[i] == '>')
			add_node(global, read_out, '>');
		if (global->line[i] == '|')
		{
			add_node(global, e_pipe, '|');
			global->p_count ++;
		}
		return (1);
	}
	return (0);
}

int	count_7(t_global *global, int i)
{
	if (global->line[i] == ' ')
	{
		if (global->tail->token == space)
			return (1);
		add_node(global, space, global->line[i]);
		return (1);
	}
	return (0);
}

int	count_8(t_global *global, int i)
{
	if (global->tail->token == string)
	{
		global->tail->str = ft_strjoin(global->tail->str, global->line[i]);
		return (1);
	}
	return (0);
}

int	count_9(t_global *global, int i)
{
	if (ft_isprint(global->line[i]))
	{
		add_node(global, string, global->line[i]);
		return (1);
	}
	return (0);
}

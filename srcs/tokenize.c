/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:39 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 05:35:40 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_global *global, t_token token, char c)
{
	t_node	*node;
	char	*tmp;

	node = (t_node *)malloc(sizeof(t_node));
	tmp = malloc(sizeof(char) * 2);
	tmp[0] = c;
	tmp[1] = '\0';
	node->str = tmp;
	node->token = token;
	node->next = NULL;
	node->prev = global->tail;
	global->tail->next = node;
	global->tail = node;
}

static void	init_global(t_global *global, char *line)
{
	t_node	*node;

	global->line = line;
	node = (t_node *)malloc(sizeof(t_node));
	node->token = -1;
	node->next = NULL;
	node->prev = NULL;
	global->head = node;
	global->tail = node;
	global->p_count = 0;
}

void	tokenize(char *line, t_global *global)
{
	int	i;

	i = 0;
	init_global(global, line);
	while (1)
	{
		if (count_1(global, i))
			break ;
		else if (count_2(global, i))
			i++;
		else if (count_4(global, &i))
			continue ;
		else if (count_5(global, &i))
			continue ;
		else if (count_6(global, i))
			i++;
		else if (count_7(global, i))
			i++;
		else if (count_8(global, i))
			i++;
		else if (count_9(global, i))
			i++;
	}
}

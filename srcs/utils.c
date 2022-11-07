/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:00:35 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/07 21:14:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13))
			return (0);
	}
	return (1);
}

void	free_global(t_global *global)
{
	t_node	*tmp;
	t_node	*node;

	node = global->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->str);
		free(tmp);
	}
	free(global->p_arr);
}

void 	ft_print_node(t_node *head)
{
	t_node	*node;
	char	token_li[13][10] = {"string", "built_in", "func", "space", "dollar", "s_quote", "d_quote", "read_in", \
							"read_in2", "read_out", "read_out2", "e_pipe", "e_error"};
	int		i;

	node = head;
	i = 0;
	while (node)
	{
		printf("i: %d, token: %s, str: %s\n", i, token_li[node->token], node->str);
		node = node->next;
		i++;
	}
}

void 	ft_print_mom(t_global *global)
{
	int		i;
	//t_node	*node;
	t_p_mom	tmp;
	char	token_li[13][10] = {"string", "built_in", "func", "space", "dollar", "s_quote", "d_quote", "read_in", \
							"read_in2", "read_out", "read_out2", "e_pipe", "e_error"};
	
	/*
	i = -1;
	while (++i <= global->p_count)
	{
		node = global->p_arr[i].head;
		while (node->next && node->token != e_pipe)
		{
			printf("i: %d, token: %s, str: %s\n", i, token_li[node->token], node->str);
			node = node->next;
		}
		printf("i: %d, token: %s, str: %s\n", i, token_li[node->token], node->str);
		node = node->next;
		if (node == NULL)
			break ;
	}
	*/
	i = -1;
	while (++i <= global->p_count)
	{
		tmp = global->p_arr[i];
		if (tmp.head)
			printf("head: %s --- tail: %s --- error: %d --- func: %d\n", \
					token_li[tmp.head->token], token_li[tmp.tail->token], \
					tmp.pipe_error, tmp.pipe_func);
		else
			printf("head: %s --- tail: %s --- error: %d --- func: %d\n", \
					NULL, NULL, tmp.pipe_error, tmp.pipe_func);
	}
}
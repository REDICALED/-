/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:00:35 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/11 15:34:48 by jinhokim         ###   ########.fr       */
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
		free(tmp->str);
		free(tmp);
		node = node->next;
	}
	free(global->p_arr);
}

void	ft_print_node(t_node *head)
{
	int		i;
	t_node	*node;
	char	token_li[13][10] = {"string", "built_in", "func", \
		"space", "dollar", "s_quote", "d_quote", "read_in", \
		"read_in2", "read_out", "read_out2", "e_pipe", "e_error"};

	node = head;
	i = 0;
	while (node)
	{
		printf("i: %2d, token: %9s, str: %s\n", i, \
						token_li[node->token], node->str);
		node = node->next;
		i++;
	}
}

void	ft_print_mom(t_global *global)
{
	int		i;
	t_p_mom	tmp;
	char	token_li[13][10] = {"string", "built_in", "func", \
		"space", "dollar", "s_quote", "d_quote", "read_in", \
		"read_in2", "read_out", "read_out2", "e_pipe", "e_error"};

	i = -1;
	while (++i <= global->p_count)
	{
		tmp = global->p_arr[i];
		if (tmp.head)
		{
			printf("head: %9s --- tail: %9s\n", \
				token_li[tmp.head->token], token_li[tmp.tail->token]);
			printf("input_fd: %d --- input_error: %d\n\n", \
				tmp.input, tmp.input_error);
		}
	}
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**cp_envp;

	i = -1;
	while (envp[++i])
		;
	cp_envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		cp_envp[i] = ft_strdup(envp[i]);
	cp_envp[i] = NULL;
	return (cp_envp);
}

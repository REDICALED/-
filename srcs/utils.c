/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:32 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 08:08:04 by jinhokim         ###   ########.fr       */
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

void	unlink_here_doc(t_global *global)
{
	int		i;
	char	*here_doc;
	char	*idx;
	char	*path;

	i = -1;
	while (++i < global->p_count)
	{
		here_doc = ft_strdup("/tmp/here_doc_");
		idx = ft_itoa(i);
		path = ft_strjoin2(here_doc, idx);
		if (access(path, F_OK) == 0)
			unlink(path);
		free(idx);
		free(path);
	}
}

void	free_global(t_global *global)
{
	t_node	*tmp;
	t_node	*node;

	//unlink_here_doc(global);
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
	printf("\n");
	while (++i <= global->p_count)
	{
		tmp = global->p_arr[i];
		if (tmp.head && tmp.tail)
		{
			printf("head: %9s --- tail: %9s\n", \
				token_li[tmp.head->token], token_li[tmp.tail->token]);
			printf("input_fd: %d --- read_error: %d\n", \
				tmp.input, tmp.read_error);
			printf("output_fd: %d --- read_error: %d\n\n", \
				tmp.output, tmp.read_error);
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

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 07:21:45 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_cmd_arr(t_p_mom *p_mom)
{
	int		i;
	t_node	*node;
	char	**cmd_arr;

	i = 0;
	node = p_mom->head;
	while (node && node->token != e_pipe)
	{
		i++;
		node = node->next;
	}
	cmd_arr = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = p_mom->head;
	while (node && node->token != e_pipe)
	{
		cmd_arr[i] = ft_strdup(node->str);
		i++;
		node = node->next;
	}
	cmd_arr[i] = 0;
	return (cmd_arr);
}

static void	run_cmd(char **cmd_arr, t_global *global)
{
	int	i;

	i = -1;
	if (ft_strncmp(cmd_arr[0], "echo", 4 + 1) == 0)
		run_echo(cmd_arr);
	else if (ft_strncmp(cmd_arr[0], "env", 3 + 1) == 0)
		run_env(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "export", 6 + 1) == 0)
		run_export(cmd_arr, global);
	while (cmd_arr[++i])
		free(cmd_arr[i]);
	free(cmd_arr);
}

void	execute(t_global *global)
{
	int		i;
	char	**cmd_arr;

	i = 0;
	if (global->head == NULL)
		return ;
	while (i <= global->p_count && global->p_arr[i].head)
	{
		printf("--- run %d cmd ---\n", i);
		cmd_arr = get_cmd_arr(&(global->p_arr[i]));
		printf("cmd: \"");
		for (int j = 0; cmd_arr[j] != NULL; j++)
		{
			if (cmd_arr[j + 1] != NULL)
				printf("%s ", cmd_arr[j]);
			else
				printf("%s\"\n", cmd_arr[j]);
		}
		run_cmd(cmd_arr, global);
		i++;
	}
}

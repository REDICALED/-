/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/17 15:13:30 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_arr(t_p_mom *p_mom)
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

int	is_builtin(char **cmd_arr)
{
	if (ft_strncmp(cmd_arr[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd_arr[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd_arr[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd_arr[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd_arr[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd_arr[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd_arr[0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	builtin_exit(t_global *global, int exit_code)
{
	if (global->p_count == 0)
		g_exit_code = exit_code;
	else
		exit(exit_code);
}

void	run_cmd(t_global *global, int idx)
{
	char	**cmd_arr;

	cmd_arr = get_cmd_arr(&(global->p_arr[idx]));
	if (ft_strncmp(cmd_arr[0], "echo", 5) == 0)
		run_echo(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "cd", 3) == 0)
		run_cd(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "pwd", 4) == 0)
		run_pwd(global);
	else if (ft_strncmp(cmd_arr[0], "env", 4) == 0)
		run_env(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "unset", 6) == 0)
		run_unset(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "export", 7) == 0)
		run_export(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "exit", 5) == 0)
		run_exit(cmd_arr);
	else
		run_execve(cmd_arr, global);
}

void	execute(t_global *global)
{
	int		stdin_dup;
	int		stdout_dup;

	stdin_dup = dup(0);
	stdout_dup = dup(1);
	if (global->p_count == 0)
		execute_single(global);
	else
		execute_pipe(global);
	dup2(stdin_dup, 0);
	dup2(stdout_dup, 1);
	close(stdin_dup);
	close(stdout_dup);
}

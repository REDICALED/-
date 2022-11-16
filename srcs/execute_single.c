/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:06:56 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 19:18:26 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_single_execve(t_global *global, char **cmd_arr)
{
	pid_t	pid;
	//int		status;

	pid = fork();
	if (pid == 0)
	{
		if (global->p_arr[0].input != -1)
			dup2(global->p_arr[0].input, STDIN_FILENO);
		if (global->p_arr[0].output != -1)
			dup2(global->p_arr[0].output, STDOUT_FILENO);
		run_execve(cmd_arr, global);
	}
	wait(NULL);
	// exit_code
}

static void	run_single_cmd(t_global *global, char **cmd_arr)
{
	if (global->p_arr[0].input != -1)
		dup2(global->p_arr[0].input, STDIN_FILENO);
	if (global->p_arr[0].output != -1)
		dup2(global->p_arr[0].output, STDOUT_FILENO);
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
		run_exit(cmd_arr, global);
}

void	execute_single(t_global *global)
{
	char	**cmd_arr;

	if (global->p_arr[0].head && global->p_arr[0].head->token != e_pipe)
	{
		cmd_arr = get_cmd_arr(&(global->p_arr[0]));
		if (is_builtin(cmd_arr) == 1)
			run_single_cmd(global, cmd_arr);
		else
			run_single_execve(global, cmd_arr);
		free_arr(cmd_arr);
	}
}

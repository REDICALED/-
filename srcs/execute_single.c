/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:06:56 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/17 15:03:11 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_single_execve(t_global *global, char **cmd_arr)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		set_execute_signal();
		if (global->p_arr[0].input != -1)
			dup2(global->p_arr[0].input, STDIN_FILENO);
		if (global->p_arr[0].output != -1)
			dup2(global->p_arr[0].output, STDOUT_FILENO);
		run_execve(cmd_arr, global);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	g_exit_code = WEXITSTATUS(status);
}

static void	run_single_builtin(t_global *global, char **cmd_arr)
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
		run_exit(cmd_arr);
}

void	execute_single(t_global *global)
{
	char	**cmd_arr;

	if (global->p_arr[0].head && global->p_arr[0].head->token != e_pipe)
	{
		cmd_arr = get_cmd_arr(&(global->p_arr[0]));
		if (is_builtin(cmd_arr) == 1)
			run_single_builtin(global, cmd_arr);
		else
			run_single_execve(global, cmd_arr);
		free_arr(cmd_arr);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 13:19:42 by jinhokim         ###   ########.fr       */
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

static void	run_cmd(t_global *global, int idx)
{
	char	**cmd_arr;

	cmd_arr = get_cmd_arr(&(global->p_arr[idx]));
	if (ft_strncmp(cmd_arr[0], "echo", 5) == 0)
		run_echo(cmd_arr);
	else if (ft_strncmp(cmd_arr[0], "cd", 3) == 0 && global->p_count == 0)
		run_cd(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "pwd", 4) == 0)
		run_pwd();
	else if (ft_strncmp(cmd_arr[0], "env", 4) == 0)
		run_env(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "unset", 6) == 0 && global->p_count == 0)
		run_unset(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "export", 7) == 0)
		run_export(cmd_arr, global);
	else if (ft_strncmp(cmd_arr[0], "exit", 5) == 0)
		run_exit(cmd_arr);
	else
		run_execve(cmd_arr, global);
}

static void	dup_child(t_global *global, int idx, int *fd)
{
	t_p_mom	*p_mom;

	p_mom = &(global->p_arr[idx]);
	if (p_mom->head->token == e_pipe)
	{
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	if (p_mom->input != -1)
		dup2(p_mom->input, STDIN_FILENO);
	if (p_mom->output != -1)
		dup2(p_mom->output, STDOUT_FILENO);
	else
	{
		if (idx < global->p_count)
			dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
}

static int	pipe_run(t_global *global, int idx)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup_child(global, idx, fd);
		run_cmd(global, idx);
	}
	else
	{
		if (idx < global->p_count)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return (pid);
}

static int	last_pipe_run(t_global *global, int idx)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup_child(global, idx, fd);
		run_cmd(global, idx);
	}
	else
	{
		if (idx < global->p_count)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return (pid);
}

void	execute(t_global *global)
{
	int		i;
	pid_t	pid_li[global->p_count + 1];
	int		status;

	i = 0;
	while (i <= global->p_count && global->p_arr[i].head)
	{
		pid_li[i] = pipe_run(global, i);
		i++;
	}
	pid_li[i] = last_pipe_run(global, i);
	i = 0;
	while (i <= global->p_count && global->p_arr[i].head)
	{
		waitpid(pid_li[i], &status, 0);
		if (i == global->p_count)
			g_exit_code = WEXITSTATUS(status);
		i++;
	}
}

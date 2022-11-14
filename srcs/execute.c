/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 06:00:33 by jinhokim         ###   ########.fr       */
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
	int		i;
	char	**cmd_arr;

	if (global->p_arr[idx].head->token == e_pipe)
		return ;
		//exit(0);
	i = -1;
	cmd_arr = get_cmd_arr(&(global->p_arr[idx]));
	printf("\n----- run %s -----\n\n", cmd_arr[0]);
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
	free_arr(cmd_arr);
}

/*
static void	run_cmd(t_global *global)
{
	int		i;
	char	**cmd_arr;
	int		fd[2];
	pid_t	pid;

	i = -1;
	cmd_arr = get_cmd_arr(&(global->p_arr[i]));
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ls 
		if (global->p_arr[~].input > 0)
			dup2(global->p_arr[~].input, STDIN_FILENO);
		close(fd[0])
		else
			dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		if (ft_strncmp(cmd_arr[0], "echo", 4 + 1) == 0)
		{
			run_echo(cmd_arr);
			sleep(5);
		}
		else if (ft_strncmp(cmd_arr[0], "pwd", 3 + 1) == 0)
		{
			run_pwd();
			sleep(1);
		}
		else if (ft_strncmp(cmd_arr[0], "env", 3 + 1) == 0)
			run_env(cmd_arr, global);
		else if (ft_strncmp(cmd_arr[0], "unset", 5 + 1) == 0)
			run_unset(cmd_arr, global);
		else if (ft_strncmp(cmd_arr[0], "export", 6 + 1) == 0)
			run_export(cmd_arr, global);
		while (cmd_arr[++i])
			free(cmd_arr[i]);
		free(cmd_arr);
	}
	if (pid > 0)
	{
		return (pid);
	}
}
*/

void	execute(t_global *global)
{
	int		i;
	//pid_t	pid_li[global->p_count + 1];
	//int		status;
	//int		fd[2];

	i = 0;
	while (i <= global->p_count && global->p_arr[i].head)
	{
		//pid_li[i] = run_cmd();

		/*
		pid_li[i] = fork();
		if (pid_li[i] == 0)
			run_cmd(global, i);
		*/
		run_cmd(global, i);
		i++;
	}
	/*
	i = 0;
	while (i <= global->p_count && global->p_arr[i].head)
	{
		waitpid(pid_li[i], &status, 0);
		if (i == global->p_count)
			g_exit_code = WEXITSTATUS(status);
		i++;
	}
	*/
}

/*
void	pipe_run()
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		child
	}
	else
	{
		// 여기서 마지막 read_out, read_out2 찾기
		return (pid);
	}
}

pid_t	*pid_li[pipe_cnt];

i = -1;
while (++i <= pipe_cnt)
{
	pid_li[i] = pipe_run()
	
	i = -1;
	int	status;
	while (++i <= pipe_cnt)
	{
		waitpid(pid_li[i], &status, NULL);
		if (i == pipe_cnt)
			g_exit_code = WEXITSTATUS(status);
	}
}
*/

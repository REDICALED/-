/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 05:36:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static void	init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

static void	free_cp_envp(t_global *global)
{
	int	i;

	i = -1;
	while (global->cp_envp[++i] != NULL)
		free(global->cp_envp[i]);
	free(global->cp_envp);
}

void	a(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	atexit(a);
	char		*line;
	t_global	global;

	init(argc, argv);
	global.cp_envp = copy_envp(envp);
	while (42)
	{
		line = readline("minishell$ ");
		if (*line)
		{
			g_exit_code = 0;
			add_history(line);
			line = ft_strtrim(line, " ");
			tokenize(line, &global);
			ft_print_node(global.head->next);
			printf("\n----- hoo start -----\n");
			if (hoo(&global) == 1)
			{
				ft_print_node(global.head);
				ft_print_mom(&global);
				free_global(&global);
				free(line);
				printf("g_exit_code: %d\n", g_exit_code);
				//continue ;
				break ;
			}
			printf("----- hoo finish -----\n\n");
			printf("----- redirection start -----\n");
			redirection(&global);
			printf("-----  redirection end  -----\n\n");
			ft_print_node(global.head);
			ft_print_mom(&global);
			printf("----- execute start -----\n");
			execute(&global);
			printf("-----  execute end  -----\n\n");
			free_global(&global);
		}
		free(line);
		printf("g_exit_code: %d\n", g_exit_code);
		break ;
	}
	free_cp_envp(&global);
	return (0);
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
		// 여기서 마지막 read_in 찾기
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

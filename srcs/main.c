/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 13:24:12 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static void	init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

/*
void	a(void)
{
	system("leaks minishell");
}
*/

int	main(int argc, char **argv, char **envp)
{
	//atexit(a);
	char		*line;
	t_global	global;

	init(argc, argv);
	global.cp_envp = copy_envp(envp);
	int tmptmp = 0;
	while (42)
	{
		line = readline("minishell$ ");
		if (line && *line)
		{
			printf("test2\n");
			printf("readline finish\n");
			g_exit_code = 0;
			add_history(line);
			line = ft_strtrim(line, " ");
			tokenize(line, &global);
			if (hoo(&global) == 1)
			{
				free_global(&global);
				free(line);
				line = NULL;
				printf("g_exit_code: %d\n", g_exit_code);
				continue ;
			}
			redirection(&global);
			ft_print_node(global.head);
			ft_print_mom(&global);
			execute(&global);
			free_global(&global);
		}
		free(line);
		// printf("g_exit_code: %d\n", g_exit_code);
		printf("%d\n", tmptmp++);
	}
	free_arr(global.cp_envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 17:44:09 by jinhokim         ###   ########.fr       */
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
	g_exit_code = 0;
	while (42)
	{
		line = readline("minishell$ ");
		line = ft_strtrim(line, " ");
		if (*line)
		{
			add_history(line);
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
		line = NULL;
		// printf("g_exit_code: %d\n", g_exit_code);
	}
	free_arr(global.cp_envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 04:40:20 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static void	init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
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
				continue ;
			}
			printf("----- hoo finish -----\n\n");
			ft_print_node(global.head);
			ft_print_mom(&global);
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
	}
	free_arr(global.cp_envp);
	return (0);
}

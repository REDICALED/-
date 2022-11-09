/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:54:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/10 05:51:49 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_global	global;

	init(argc, argv);
	global.cp_envp = copy_envp(envp);
	while (42)
	{
		line = readline("minishell$ ");
		if (*line)
		{
			add_history(line);
			line = ft_strtrim(line, " ");
			tokenize(line, &global);
			ft_print_node(global.head->next);
			hoo(&global);
			ft_print_node(global.head);
			ft_print_mom(&global);
			free_global(&global);
		}
		free(line);
	}
	free_cp_envp(&global);
	return (0);
}

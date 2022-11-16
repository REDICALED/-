/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 20:11:01 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

static void	init(int argc, char **argv, char **envp, t_global *global)
{
	(void)argc;
	(void)argv;
	global->cp_envp = copy_envp(envp);
}

static void	minishell(t_global *global)
{
	char	*line;

	line = readline("minishell$ ");
	line = ft_strtrim(line, " ");
	if (*line)
	{
		add_history(line);
		tokenize(line, global);
		if (hoo(global) == 1)
		{
			free_global(global);
			free(line);
			return ;
		}
		redirection(global);
		execute(global);
		free_global(global);
	}
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	init(argc, argv, envp, &global);
	while (42)
		minishell(&global);
	free_arr(global.cp_envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:54:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/10 05:12:21 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

void	a(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	atexit(a);
	char		*line;
	t_global	global;
	int			i;

	(void)argc;
	(void)argv;
	global.cp_envp = copy_envp(envp);
	while (42)
	{
		line = readline("minishell$ ");
		if (*line)
		{
			line = ft_strtrim(line, " ");
			tokenize(line, &global);
			ft_print_node(global.head->next);
			hoo(&global);
			ft_print_node(global.head);
			ft_print_mom(&global);
			free_global(&global);
		}
		free(line);
		break ;
	}
	i = -1;
	while (global.cp_envp[++i] != NULL)
		free(global.cp_envp[i]);
	free(global.cp_envp);
	return (0);
}

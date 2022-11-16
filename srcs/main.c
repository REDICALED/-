/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:04 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 22:36:30 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static void	init(int argc, char **argv, char **envp, t_global *global)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	global->cp_envp = copy_envp(envp);
	g_exit_code = 0;
	(void)argc;
	(void)argv;
}

static void	minishell(t_global *global)
{
	char	*line;

	line = readline("minishell$ ");
	line = ft_strtrim(line, " ");
	if (line && *line)
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
	t_global		global;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	init(argc, argv, envp, &global);
	while (42)
	{
		set_signal();
		minishell(&global);
	}
	free_arr(global.cp_envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

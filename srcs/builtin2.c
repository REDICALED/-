/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 05:28:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 22:25:10 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_remove(t_global *global, int j)
{
	free(global->cp_envp[j]);
	while (global->cp_envp[++j])
		global->cp_envp[j - 1] = global->cp_envp[j];
	global->cp_envp[j - 1] = NULL;
}

void	run_unset(char **cmd_arr, t_global *global)
{
	int		i;
	int		j;
	char	**dict;

	i = 0;
	while (cmd_arr[++i])
	{
		j = -1;
		while (global->cp_envp[++j])
		{
			dict = env_split(global->cp_envp[j]);
			if (dict == NULL)
			{
				if (ft_strncmp(cmd_arr[i], global->cp_envp[j], \
						ft_strlen(global->cp_envp[j]) + 1) == 0)
					env_remove(global, j);
			}
			else if (ft_strncmp(cmd_arr[i], dict[0], \
					ft_strlen(dict[0]) + 1) == 0)
				env_remove(global, j);
			free_arr(dict);
		}
	}
	builtin_exit(global, 0);
}

void	run_env(char **cmd_arr, t_global *global)
{
	int	i;

	if (cmd_arr[1])
	{
		ft_putstr_fd("usage: env [with no options or arguments]\n", 2);
		builtin_exit(global, 1);
		return ;
	}
	i = -1;
	while (global->cp_envp[++i])
	{
		if (env_strchr(global->cp_envp[i], '=') >= 0)
			printf("%s\n", global->cp_envp[i]);
	}
	builtin_exit(global, 0);
}

void	run_exit(char **cmd_arr)
{
	int	i;

	if (cmd_arr[1] == NULL)
		exit(0);
	i = -1;
	while (cmd_arr[1][++i])
	{
		if (ft_isdigit(cmd_arr[1][i]) == 0)
		{
			ft_putstr_fd("exit: a: numeric argument required\n", 2);
			free_arr(cmd_arr);
			exit(255);
		}
	}
	if (cmd_arr[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		free_arr(cmd_arr);
		exit(1);
	}
	exit(ft_atoi(cmd_arr[1]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 03:08:21 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_echo(char **cmd_arr)
{
	int	i;

	i = 1;
	if (cmd_arr[i] && ft_strncmp(cmd_arr[1], "-n", 3) == 0)
		i++;
	while (cmd_arr[i])
	{
		if (cmd_arr[i + 1] != NULL)
			printf("%s ", cmd_arr[i]);
		else
			printf("%s", cmd_arr[i]);
		i++;
	}
	if (cmd_arr[1] == NULL || \
		(cmd_arr[1] && ft_strncmp(cmd_arr[1], "-n", 3) != 0))
		printf("\n");
}

void	run_cd(char **cmd_arr, t_global *global)
{
	(void)global;
	if (cmd_arr[1] == NULL)
	{
		printf("cd home dir\n");
		return ;
	}
	printf("cd %s\n", cmd_arr[1]);
}

void	run_pwd(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * 4096);
	getcwd(path, 4096);
	printf("%s\n", path);
	free(path);
}

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
			free(dict[0]);
			free(dict[1]);
			free(dict);
		}
	}
}

void	run_env(char **cmd_arr, t_global *global)
{
	int	i;

	if (cmd_arr[1])
	{
		ft_putstr_fd("usage: env [with no options or arguments]\n", 2);
		//g_exit_code = 1;
		//exit(1);
		return ;
	}
	i = -1;
	while (global->cp_envp[++i])
	{
		if (env_strchr(global->cp_envp[i], '=') >= 0)
			printf("%s\n", global->cp_envp[i]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/17 16:03:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_echo(char **cmd_arr, t_global *global)
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
	builtin_exit(global, 0);
}

static void	cd_env_update(char *old, char *new, t_global *global)
{
	int		i;
	char	**env_dict;

	i = -1;
	while (global->cp_envp[++i])
	{
		env_dict = env_split(global->cp_envp[i]);
		if (ft_strncmp("OLDPWD", env_dict[0], \
			ft_strlen(env_dict[0]) + 1) == 0)
		{
			free(global->cp_envp[i]);
			global->cp_envp[i] = ft_strjoin3("OLDPWD=", old);
		}
		else if (ft_strncmp("PWD", env_dict[0], \
			ft_strlen(env_dict[0]) + 1) == 0)
		{
			free(global->cp_envp[i]);
			global->cp_envp[i] = ft_strjoin3("PWD=", new);
		}
		free_arr(env_dict);
	}
}

void	run_cd(char **cmd_arr, t_global *global)
{
	char	*old;
	char	*new;

	old = getcwd(NULL, 4096);
	if ((cmd_arr[1] == NULL) || \
		(cmd_arr[1] && ft_strncmp(cmd_arr[1], "~", 2) == 0))
	{
		new = find_env_value("$HOME", global->cp_envp);
		chdir(new);
	}
	else if (chdir(cmd_arr[1]) == 0)
		new = getcwd(NULL, 4096);
	else
	{
		ft_putstr_fd(cmd_arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(old);
		builtin_exit(global, 1);
		return ;
	}	
	cd_env_update(old, new, global);
	free(old);
	free(new);
	builtin_exit(global, 0);
}

void	run_pwd(t_global *global)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * 4096);
	getcwd(path, 4096);
	printf("%s\n", path);
	free(path);
	builtin_exit(global, 0);
}

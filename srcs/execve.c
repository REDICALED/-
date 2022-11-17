/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 05:36:20 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/17 16:32:15 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env_path(t_global *global)
{
	char	*value;
	char	**paths;

	value = find_env_value("$PATH", global->cp_envp);
	paths = ft_split(value, ':');
	free(value);
	return (paths);
}

static char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*joined_cmd;
	char	*ret_cmd;

	if (*cmd == 0)
		return (NULL);
	i = 0;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	joined_cmd = ft_strjoin3("/", cmd);
	while (path[i])
	{
		ret_cmd = ft_strjoin3(path[i++], joined_cmd);
		if (access(ret_cmd, X_OK) != -1)
		{
			free(joined_cmd);
			return (ret_cmd);
		}
		free(ret_cmd);
	}
	free(joined_cmd);
	return (NULL);
}

void	run_execve(char **cmd_arr, t_global *global)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	paths = get_env_path(global);
	cmd_path = get_cmd(paths, cmd_arr[0]);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(paths);
		free_arr(cmd_arr);
		exit(127);
	}
	if (execve(cmd_path, cmd_arr, global->cp_envp) == -1)
	{
		ft_putstr_fd("execve error\n", 2);
		exit(1);
	}
}

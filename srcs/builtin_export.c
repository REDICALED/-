/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 06:47:48 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/17 16:17:29 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sort_envp(char **cp_envp)
{
	int		i;
	int		j;
	char	**tmp_envp;
	char	*tmp;

	i = -1;
	tmp_envp = copy_envp(cp_envp);
	while (tmp_envp[++i])
	{
		j = i;
		while (tmp_envp[++j])
		{
			if (ft_strncmp(tmp_envp[i], tmp_envp[j], \
				ft_strlen(tmp_envp[j])) > 0)
			{
				tmp = tmp_envp[j];
				tmp_envp[j] = tmp_envp[i];
				tmp_envp[i] = tmp;
			}
		}
	}
	return (tmp_envp);
}

static void	print_export(t_global *global)
{
	int		i;
	char	**tmp_envp;
	char	**dict;

	i = -1;
	tmp_envp = sort_envp(global->cp_envp);
	while (tmp_envp[++i])
	{
		if (env_strchr(tmp_envp[i], '=') == -1)
			printf("declare -x %s\n", tmp_envp[i]);
		else
		{
			dict = env_split(tmp_envp[i]);
			printf("declare -x ");
			printf("%s=\"", dict[0]);
			printf("%s\"\n", dict[1]);
			free_arr(dict);
		}
	}
	free_arr(tmp_envp);
}

static void	env_append(char *cmd, t_global *global)
{
	int		i;
	char	**tmp_envp;

	i = -1;
	while (global->cp_envp[++i])
		;
	tmp_envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (global->cp_envp[++i])
		tmp_envp[i] = ft_strdup(global->cp_envp[i]);
	tmp_envp[i] = ft_strdup(cmd);
	tmp_envp[i + 1] = NULL;
	free_arr(global->cp_envp);
	global->cp_envp = tmp_envp;
}

static int	env_update(char *cmd, char **cmd_dict, t_global *global)
{
	int		i;
	char	**env_dict;

	i = -1;
	while (global->cp_envp[++i])
	{
		env_dict = env_split(global->cp_envp[i]);
		if (ft_strncmp(cmd_dict[0], env_dict[0], \
			ft_strlen(env_dict[0]) + 1) == 0)
		{
			free(global->cp_envp[i]);
			global->cp_envp[i] = ft_strdup(cmd);
			free_arr(env_dict);
			return (1);
		}
		free_arr(env_dict);
	}
	return (0);
}

void	run_export(char **cmd_arr, t_global *global)
{
	int		i;
	char	**cmd_dict;

	i = 0;
	if (cmd_arr[1])
	{
		if (global->p_count != 0)
			exit(0);
		while (cmd_arr[++i])
		{
			cmd_dict = env_split(cmd_arr[i]);
			if (cmd_dict == NULL)
				continue ;
			if (env_update(cmd_arr[i], cmd_dict, global) == 1)
				;
			else
				env_append(cmd_arr[i], global);
			free_arr(cmd_dict);
		}
		builtin_exit(global, 0);
		return ;
	}
	print_export(global);
	builtin_exit(global, 0);
}

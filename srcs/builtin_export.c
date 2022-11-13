/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 06:47:48 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 07:23:24 by jinhokim         ###   ########.fr       */
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
			if (ft_strncmp(tmp_envp[i], tmp_envp[j], ft_strlen(tmp_envp[j])) > 0)
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
			free(dict[0]);
			free(dict[1]);
			free(dict);
		}
	}
	i = -1;
	while (tmp_envp[++i])
		free(tmp_envp[i]);
	free(tmp_envp);
}

static void	append_env(char **cmd_arr, t_global *global)
{
	int		i;
	int		arr_len;
	char	**tmp_envp;

	i = -1;
	arr_len = -1;
	while (global->cp_envp[++i])
		;
	while (cmd_arr[++arr_len])
		;
	tmp_envp = (char **)malloc(sizeof(char *) * (i + arr_len));
	i = -1;
	while(global->cp_envp[++i])
		tmp_envp[i] = ft_strdup(global->cp_envp[i]);
	arr_len = 0;
	while(cmd_arr[++arr_len])
		tmp_envp[i + arr_len - 1] = ft_strdup(cmd_arr[arr_len]);
	tmp_envp[i + arr_len - 1] = NULL;
	i = -1;
	while (global->cp_envp[++i])
		free(global->cp_envp[i]);
	free(global->cp_envp);
	global->cp_envp = tmp_envp;
}

void	run_export(char **cmd_arr, t_global *global)
{
	if (cmd_arr[1] && global->p_count == 0)
	{
		append_env(cmd_arr, global);
		return ;
	}
	print_export(global);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 20:04:21 by jinhokim         ###   ########.fr       */
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

void	run_cd(char **cmd_arr, t_global *global)
{
	char	*value;

	if (cmd_arr[1] == NULL || \
		(cmd_arr[1] && ft_strncmp(cmd_arr[1], "~", 2) == 0))
	{
		value = find_env_value("$HOME", global->cp_envp);
		chdir(value);
		free(value);
	}
	else
	{
		if (chdir(cmd_arr[1]) != 0)
		{
			ft_putstr_fd(cmd_arr[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			builtin_exit(global, 1);
			return ;
		}	
	}
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

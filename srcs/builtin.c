/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 16:37:19 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_echo(char **cmd_arr, t_global *global)
{
	int	i;

	(void)global;
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

	if (cmd_arr[1] == NULL)
	{
		value = find_env_value("$HOME", global->cp_envp);
		printf("cd home dir: %s\n", value);
		free(value);
		builtin_exit(global, 0);
	}
	printf("cd %s\n", cmd_arr[1]);
	builtin_exit(global, 0);
}

void	run_pwd(t_global *global)
{
	char	*path;

	(void)global;
	path = (char *)malloc(sizeof(char) * 4096);
	getcwd(path, 4096);
	printf("%s\n", path);
	free(path);
	builtin_exit(global, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/12 06:50:04 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_echo(char **cmd_arr)
{
	int	i;

	printf("\n--- echo start ---\n");
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
	printf("\n---  echo end  ---\n");
}

static char	*env_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	while (*(s))
	{
		if (*(s) == char_c)
			return ((char *)(s));
		s++;
	}
	if (char_c == '\0')
		return ((char *)s);
	return (0);
}

void	run_env(char **cmd_arr, t_global *global)
{
	int	i;

	printf("\n--- env start ---\n");
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
		if (env_strchr(global->cp_envp[i], '='))
			printf("%s\n", global->cp_envp[i]);
	}
	printf("\n---  env end  ---\n");
}

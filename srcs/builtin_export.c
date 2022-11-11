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

/*
static void	sort_envp(char **cp_envp)
{
	int	i;
	int	j;

	i = -1;
	while (cp_envp[++i])
	{
		j = i + 1;
		while (cp_envp[i][++j])
		{
			if (ft_strcmp(cp_envp[i][j], cp_envp[i][j]) > 0)
			{
            	strcpy(temp, strings[j]);
            	strcpy(strings[j], strings[j+1]);
            	strcpy(strings[j+1], temp);
			}
		}
	}
}
*/

static void	print_export(t_global *global)
{
	int	i;

	i = -1;
	while (global->cp_envp[++i])
		printf("%s\n", global->cp_envp[i]);
}

void	run_export(char **cmd_arr, t_global *global)
{
	printf("\n--- export start ---\n");
	if (cmd_arr[1])
	{
		return ;
	}
	print_export(global);
	printf("\n---  export end  ---\n");
}

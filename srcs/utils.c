/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:32 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 21:54:58 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_here_doc(t_global *global)
{
	int		i;
	char	*here_doc;
	char	*idx;
	char	*path;

	i = -1;
	while (++i < global->p_count)
	{
		here_doc = ft_strdup("/tmp/here_doc_");
		idx = ft_itoa(i);
		path = ft_strjoin2(here_doc, idx);
		if (access(path, F_OK) == 0)
			unlink(path);
		free(idx);
		free(path);
	}
}

void	free_global(t_global *global)
{
	t_node	*tmp;
	t_node	*node;

	unlink_here_doc(global);
	node = global->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->str);
		free(tmp);
	}
	free(global->p_arr);
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**cp_envp;

	i = -1;
	while (envp[++i])
		;
	cp_envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		cp_envp[i] = ft_strdup(envp[i]);
	cp_envp[i] = NULL;
	return (cp_envp);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

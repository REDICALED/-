/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hoo_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:19 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 08:52:29 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_strchr(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

char	**env_split(char *str)
{
	int		i;
	int		str_len;
	char	**dict;

	i = env_strchr(str, '=');
	if (i == -1)
		return (NULL);
	str_len = (int)ft_strlen(str);
	dict = (char **)malloc(sizeof(char *) * 3);
	dict[0] = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(dict[0], str, i + 1);
	dict[1] = (char *)malloc(sizeof(char) * (str_len - i));
	ft_strlcpy(dict[1], &str[i + 1], str_len - i);
	dict[2] = NULL;
	return (dict);
}

char	*find_env_value(char *str, char **cp_envp)
{
	int		i;
	char	**dict;
	char	*value;

	i = -1;
	while (cp_envp[++i])
	{
		dict = env_split(cp_envp[i]);
		if (dict == NULL)
			continue ;
		if (ft_strncmp(&str[1], dict[0], ft_strlen(dict[0]) + 1) == 0)
		{
			value = ft_strdup(dict[1]);
			free_arr(dict);
			return (value);
		}
		free_arr(dict);
	}
	value = ft_strdup("");
	return (value);
}

void	hoo_dollar(t_node *node, t_global *global)
{
	char	*value;

	node->token = string;
	if ((int)ft_strlen(node->str) == 1)
		return ;
	if (ft_strncmp(node->str, "$?", 3) == 0)
		value = ft_itoa(g_exit_code);
	else
		value = find_env_value(node->str, global->cp_envp);
	free(node->str);
	node->str = value;
}

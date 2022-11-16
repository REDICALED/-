/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hoo_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:36:39 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 18:05:45 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	interpret_join(char **res, char *str, int i, char **cp_envp)
{
	int		j;
	char	*key;
	char	*value;

	if (str[i + 1] == '?')
	{
		value = ft_itoa(g_exit_code);
		*res = ft_strjoin2(*res, value);
		free(value);
		return (2);
	}
	j = 1;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_'))
		j++;
	key = (char *)malloc(sizeof(char) * (j + 1));
	ft_strlcpy(key, &str[i], j + 1);
	value = find_env_value(key, cp_envp);
	*res = ft_strjoin2(*res, value);
	free(key);
	free(value);
	return (j);
}

char	*interpret_double(char *str, char **cp_envp)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			if (str[i + 1] == '$')
				i += 2;
			else
				i += interpret_join(&res, str, i, cp_envp);
		}
		else
			res = ft_strjoin(res, str[i++]);
	}
	return (res);
}

void	hoo_double_quote(t_node *node, t_global *global)
{
	char	*res;

	node->token = string;
	res = interpret_double(node->str, global->cp_envp);
	free(node->str);
	node->str = res;
}

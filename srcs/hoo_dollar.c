#include "minishell.h"

char	**env_split(char *str)
{
	char	**dict;
	int		i;
	int		str_len;

	dict = (char **)malloc(sizeof(char *) * 3);
	i = 0;
	str_len = (int)ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
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
		if (ft_strncmp(&str[1], dict[0], ft_strlen(dict[0]) + 1) == 0)
		{
			value = ft_strdup(dict[1]);
			free(dict[0]);
			free(dict[1]);
			free(dict);
			return (value);
		}
		free(dict[0]);
		free(dict[1]);
		free(dict);
	}
	value = ft_strdup("");
	return (value);
}

void	hoo_dollar(t_node *node, t_global *global)
{
	char	*value;

	printf("=== dollar start ===\n");
	printf("str: %s, str_len: %d\n", node->str, (int)ft_strlen(node->str));
	node->token = string;
	if ((int)ft_strlen(node->str) == 1)
		return ;
	if (ft_strncmp(node->str, "$?", 3) == 0)
		value = ft_itoa(g_exit_code);
	else
		value = find_env_value(node->str, global->cp_envp);
	free(node->str);
	node->str = value;
	printf("===  dollar end  ===\n");
	printf("str: %s, str_len: %d\n\n", node->str, (int)ft_strlen(node->str));
}

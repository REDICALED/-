#include "minishell.h"

static char	*get_value(char *str, char **cp_envp)
{
	int		i;
	char	**dict;
	char	*value;

	i = -1;
	while (cp_envp[++i])
	{
		dict = ft_split(cp_envp[i], '=');
		if (ft_strncmp(str, dict[0], ft_strlen(dict[0]) + 1) == 0)
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
	if (ft_strncmp(node->str, "?", 2) == 0)
		value = ft_itoa(g_exit_code);
	else
		value = get_value(node->str, global->cp_envp);
	free(node->str);
	node->str = value;
	printf("===  dollar end  ===\n");
	printf("str: %s, str_len: %d\n\n", node->str, (int)ft_strlen(node->str));
}

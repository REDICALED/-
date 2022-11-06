#include "minishell.h"
#include "libft.h"

int	count_6(t_global *global, int i)
{
	if (global->line[i] == '<' || global->line[i] == '>' || global->line[i] == '|')
	{
		if (global->line[i] == '<')
			add_node(global, read_in, '<');
		if (global->line[i] == '>')
			add_node(global, read_out, '>');
		if (global->line[i] == '|')
			add_node(global, e_pipe, '|');
		return (1);
	}
	return (0);
}

// space 토큰 추가
int	count_7(t_global *global, int i)
{
	if (global->line[i] == ' ')
	{
		if (global->tail->token == space)
			return (1);
		add_node(global, space, global->line[i]);
		return (1);
	}
	return (0);
}

int	count_8(t_global *global, int i)
{
	if (global->tail->token == string)
	{
		global->tail->str = ft_strjoin(global->tail->str, global->line[i]);
		return (1);
	}
	return (0);
}

int	count_9(t_global *global, int i)
{
	if (ft_isprint(global->line[i]))
	{
		add_node(global, string, global->line[i]);
		return (1);
	}
	return (0);
}

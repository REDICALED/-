#include "minishell.h"
#include "libft.h"

int	is_eof(t_global *global, int i)
{
	if (global->line[i] == 0)
	{
		global->token_count += 1;
		return (1);
	}
	return (0);
}

int	is_2(t_global *global, int i)
{
	if (i >= 1 && (global->line[i - 1] == '<' || global->line[i - 1] == '>'))
	{
		if (global->line[i - 1] == '<' && global->line[i] == '<')
		{
			global->tail->str = "<<";
		}
		else if (global->line[i - 1] == '>' && global->line[i] == '>')
		{
			global->tail->str = ">>";
		}
		return (1);
	}
	return (0);
}
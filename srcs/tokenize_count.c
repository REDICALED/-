#include "minishell.h"
#include "libft.h"

int	count_1(t_global *global, int i)
{
	if (global->line[i] == 0)
		return (1);
	return (0);
}

/*
<<< 같은 경우 
<
<
<
이런식으로 저장되는데, 아래 조건을 추가해주는 방식으로 문제 해결
&& global->tail->token != read_in2 && global->tail->token != read_out2)
*/
int	count_2(t_global *global, int i)
{
	if (i >= 1 && (global->line[i - 1] == '<' || global->line[i - 1] == '>') \
		&& global->tail->token != read_in2 && global->tail->token != read_out2)
	{
		if (global->line[i - 1] == '<' && global->line[i] == '<')
		{
			global->tail->token = read_in2;
			global->tail->str = ft_strjoin(global->tail->str, '<');
			return (1);
		}
		else if (global->line[i - 1] == '>' && global->line[i] == '>')
		{
			global->tail->token = read_out2;
			global->tail->str = ft_strjoin(global->tail->str, '>');
			return (1);
		}
	}
	return (0);
}

int	count_4(t_global *global, int *i)
{
	if (global->line[*i] == '\'')
	{
		add_node(global, s_quote, '\'');
		while (global->line[++(*i)] != '\'')
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
		global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
		(*i)++;
		return (1);
	}
	else if (global->line[*i] == '\"')
	{
		add_node(global, d_quote, '\"');
		while (global->line[++(*i)] != '\"')
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
		global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

int	count_5(t_global *global, int *i)
{
	int	flag;

	flag = 0;
	if (global->line[*i] == '$')
	{
		add_node(global, dollar, '$');
		(*i)++;
		if (global->line[*i] == '?')
		{
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
			(*i)++;
			return (1);
		}
		while (ft_isalnum(global->line[*i]) != 0 || global->line[*i] == '_')
		{
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
			(*i)++;
			flag = 1;
		}
		if (flag == 0 && (ft_strchr("<>|", global->line[*i]) == NULL))
		{
			global->tail->str = ft_strjoin(global->tail->str, global->line[*i]);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

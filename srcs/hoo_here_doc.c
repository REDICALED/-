#include "minishell.h"

static int	here_doc_check(t_node *node)
{
	if (node->token == e_pipe || node->token == read_in || \
		node->token == read_in2 || node->token == read_out || \
		node->token == read_out2)
	{
		node->prev->token = e_error;
		return (1);
	}
	return (0);
}

static void	here_doc(t_node *node, t_global *global)
{
	int		fd;
	char	*tmp_line;
	char	*line;

	fd = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (42)
	{
		tmp_line = readline("heredoc> ");
		if (ft_strncmp(line, node->str, ft_strlen(node->str) + 1) == 0)
		{
			free(tmp_line);
			break ;
		}
		line = interpret_double(tmp_line, global->cp_envp);
		free(tmp_line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(node->str);
	node->str = ft_strdup("/tmp/here_doc");
	node->token = string;
	close(fd);
}

/*
void	hoo_here_doc(t_node *node)
{
	node = node->next;
	if (node == NULL)
		node->token = e_error;
	else
	{
		if (node->token == space)
		{
			node = node->next;
			if (node == NULL)
			{
				node->prev->prev->token = e_error;
				return ;
			}
		}
		if (here_doc_check(node))
			return ;
		node->prev->token = read_in;
		if (node->token == string || node->token == dollar || \
			node->token == d_quote || node->token == s_quote)
			here_doc(node);
	}
}
*/

void	hoo_here_doc(t_node *node, t_global *global)
{
	if (node->next == NULL || (node->next->token == space && \
			node->next->next == NULL))
		node->token = e_error;
	else
	{
		if (node->next->token == space)
		{
			node->next = node->next->next;
			free(node->next->prev->str);
			free(node->next->prev);
			node->next->prev = node;
		}
		if (here_doc_check(node->next))
			return ;
		free(node->str);
		node->str = ft_strdup("<");
		node->token = read_in;
		node = node->next;
		if (node->token == string || node->token == dollar || \
			node->token == d_quote || node->token == s_quote)
			here_doc(node, global);
	}
}

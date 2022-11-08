#include "minishell.h"

static void	here_doc(t_node *node)
{
	int		fd;
	char	*line;

	fd = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (42)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, node->str, ft_strlen(node->str) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

static int	here_doc_check(t_node *node)
{
	if (node->token == e_pipe || node->token == read_in || \
		node->token == read_in2 || node->token == read_out || \
		node->token == read_out2)
	{
		node = node->prev;
		if (node->token == space)
			node = node->prev;
		node->token = e_error;
		return (1);
	}
	return (0);
}

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
		if (node->token == string || node->token == dollar || \
			node->token == d_quote)
		{
			node->token = s_quote;
			here_doc(node);
		}
	}
}

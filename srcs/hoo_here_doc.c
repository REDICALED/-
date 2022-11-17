/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hoo_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:35:32 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/15 05:12:19 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	here_doc_write(int fd, t_node *node)
{
	char	*line;

	line = readline("heredoc> ");
	if (ft_strncmp(line, node->str, ft_strlen(node->str) + 1) == 0)
	{
		free(line);
		return (1);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

static void	here_doc(t_node *node, int i)
{
	char	*here_doc;
	char	*idx;
	char	*path;
	int		fd;

	here_doc = ft_strdup("/tmp/here_doc_");
	idx = ft_itoa(i);
	path = ft_strjoin2(here_doc, idx);
	free(idx);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (42)
	{
		if (here_doc_write(fd, node) == 1)
			break ;
	}
	free(node->str);
	node->str = path;
	node->token = string;
	close(fd);
}

void	hoo_here_doc(t_node *node, int i)
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
			here_doc(node, i);
	}
}

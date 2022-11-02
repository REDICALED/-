/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:53:27 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/02 15:53:36 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef enum
{
	word,
	func,
	//space,
	dollar,
	s_quote,
	d_quote,
	red_in,
	red_out,
	red_out2,
	pipe,
	here_doc,
}		e_token;

typedef	struct s_node
{
	char	*str;
	t_info	info;
	e_token	token;
	t_node	prev;
	t_node	next;
}				t_node;

typedef struct s_info
{
	int		quote;
	int		pipe;
}				t_info;

typedef	struct s_token_list
{
	t_node	head;
	t_node	tail;
	t_info	info;
	int		len;
}				t_token_list;

ABC "$CC"


int	is_space(char *line);
int	ft_strlen(char *line);

#endif

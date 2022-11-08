/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:40:10 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/08 22:40:12 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <./readline/readline.h>
# include <./readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"

typedef enum s_token
{
	string,
	built_in,
	func,
	space,
	dollar,
	s_quote,
	d_quote,
	read_in,
	read_in2,
	read_out,
	read_out2,
	e_pipe,
	e_error
}		t_token;

typedef struct s_node
{
	char			*str;
	t_token			token;
	t_token			error_token;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_p_mom
{
	int		pipe_error;
	int		pipe_func;
	t_node	*head;
	t_node	*tail;
}				t_p_mom;

typedef struct s_global
{
	char		**cp_envp;
	int			p_count;
	t_p_mom		*p_arr;
	char		*line;
	t_node		*head;
	t_node		*tail;
}				t_global;

//tokenize_util.c
int		count_1(t_global *global, int i);
int		count_2(t_global *global, int i);
int		count_3(t_global *global, int *i);
int		count_4(t_global *global, int *i);
int		count_5(t_global *global, int *i);

//tokenize_util2.c
int		count_6(t_global *global, int i);
int		count_7(t_global *global, int i);
int		count_8(t_global *global, int i);
int		count_9(t_global *global, int i);

//util.c
int		is_space(char *line);
void	free_global(t_global *global);
void	ft_print_node(t_node *head);
void	ft_print_mom(t_global *global);
char	**copy_envp(char **envp);

//tokenize.c
void	add_node(t_global *global, t_token token, char c);
void	tokenize(char *line, t_global *global);

//hoo.c
void	pipe_mom_init(t_global *global);
void	hoo_init(t_global *global);

//void	hoo_token_check_loop(t_node *node);
void	hoo_token_check(t_global *global);
void	hoo(t_global *global);

//hoo_here_doc.c
void	hoo_here_doc(t_node *node);

//hoo_dollar.c
void	hoo_dollar(t_node *node, t_global *global);

#endif

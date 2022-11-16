/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:40:10 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/16 17:29:57 by jinhokim         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>

int	g_exit_code;

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
	int		i;
	int		input;
	int		output;
	int		read_error;
	int		pipe_error;
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

//util.c
int		is_space(char *line);
void	unlink_here_doc(t_global *global);
void	free_global(t_global *global);
void	ft_print_node(t_node *head);
void	ft_print_mom(t_global *global);
char	**copy_envp(char **envp);
void	free_arr(char **arr);

//tokenize_util.c
int		count_1(t_global *global, int i);
int		count_2(t_global *global, int i);
int		count_3(t_global *global, int *i);
int		count_4(t_global *global, int *i);

//tokenize_util2.c
int		count_5(t_global *global, int *i);
int		count_6(t_global *global, int i);
int		count_7(t_global *global, int i);
int		count_8(t_global *global, int i);
int		count_9(t_global *global, int i);

//tokenize.c
void	add_node(t_global *global, t_token token, char c);
void	tokenize(char *line, t_global *global);

//hoo.c
int		hoo(t_global *global);

//hoo_here_doc.c
void	hoo_here_doc(t_node *node, int i);

//hoo_dollar.c
int		env_strchr(char *s, char c);
char	**env_split(char *str);
char	*find_env_value(char *str, char **cp_envp);
void	hoo_dollar(t_node *node, t_global *global);

//hoo_double_quote.c
char	*interpret_double(char *str, char **cp_envp);
void	hoo_double_quote(t_node *node, t_global *global);

//hoo_string.c
void	hoo_string(t_node *node, t_global *global, t_p_mom *p_mom);
void	hoo_space_check(t_p_mom *p_mom);

//redirection.c
void	redirection(t_global *global);

//redirection_utils.c
void	remove_redirection_util(t_global *global, t_node *node, t_node *tmp);

//builtin.c
void	run_echo(char **cmd_arr, t_global *global);
void	run_cd(char **cmd_arr, t_global *global);
void	run_pwd(t_global *global);

//builtin.c
void	run_unset(char **cmd_arr, t_global *global);
void	run_env(char **cmd_arr, t_global *global);
void	run_exit(char **cmd_arr, t_global *global);

//builtin_export.c
void	run_export(char **cmd_arr, t_global *global);

//execute_utils.c
char	**get_cmd_arr(t_p_mom *p_mom);
int 	is_builtin(t_global *global, int idx);
void 	builtin_exit(t_global *global, int exit_code);

//execute.c
void	run_cmd(t_global *global, int idx);
void	execute(t_global *global);

//execute_pipe.c
void	execute_pipe(t_global *global);

//execute_single.c
void	run_execve(char **cmd_arr, t_global *global);

//execute_execve.c
void	execute_single(t_global *global);

#endif

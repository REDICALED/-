/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:53:27 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 18:19:35 by jinhokim         ###   ########.fr       */
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

typedef	struct s_node
{
	*input;
	
}				t_nodea;

typedef struct s_cmd_list
{
	char		**env;
	int			pipe;
}					t_cmd_list;


#endif


토큰화를 하고, 실행부분을 아주 간단하게 해서 눈으로 확인
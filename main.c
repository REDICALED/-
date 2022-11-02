/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:54:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/02 15:13:43 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node  *add_node()
{
    t_node  *node;

    node = (t_node *)malloc(sizeof(t_node));
    node->str = NULL;
    node->token = NULL;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

void    tokenize(char *line, t_node *token_list)
{
    int i;
    t_info  *info;
    
    printf("%s\n", line);
    i = -1;
    info = (t_info *)malloc(sizeof(t_info));
    while (++i < ft_strlen(line))
    {
        if (line[i] == '<')
        {
            token_list
        }

    }
}

int main(int argc, char **argv, char **envp)
{
    char            *line;
    t_token_list    token_list;

    (void)argc;
    (void)argv;
    (void)envp;
    while (42)
    {
        line = readline("minishell $ ");
        // finish
        if (line == NULL || is_space(line))
        {
            free(line);
            break ;
        }
        // parsing start
        if (*line)
        {
            tokenize(line, &token_list);
        }
        free(line);
    }
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:54:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/06 23:29:17 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char            *line;
    t_global    global;

    (void)argc;
    (void)argv;
    (void)envp;
    while (42)
    {
        line = readline("minishell $ ");
        // parsing start
		if (*line)
        {
            tokenize(line, &global);
            free_global(&global);
        }
        free(line);
    }
    return (0);
}

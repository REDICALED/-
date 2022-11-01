/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:54:21 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/30 09:32:39 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
    char    **t_envp;

    argc = 1;
    argv = NULL;
    t_envp = envp;
    while ((line = readline("minishell $ ")))
    {
        if (*line)
        {
            printf("%s\n", line);
        }
        free(line);
    }
    return (0);
}

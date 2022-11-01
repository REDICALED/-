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
    while ((line = "readline("minishell $ )))
    {
        if (*line)
        {
            printf("%s\n", line);
        }
		//토큰화
		line->토큰화->A_struct
		B_struct
		input (input file, <, <<), function(ls, grep ...), A_struct에 넣을 정보 and output, tmp file (필요시),
		
		//리디렉션, 히어독 처리
		//후처리, 파싱
		//struct에 정보 다 담겨진 상태에서~
		free(line);
		
		
		
		
		
//		if (파이프 있으면?)
//		{
//			fork();
//			while (파이프 갯수)
//			{
//				fork();
//				exec();
//			}
//			while (파이프 갯수)
//			{
//				wait(NULL);
//			}
//		}
//		else
//		{
//			fork();
//			exec();
//		}
    }
    return (0);
}

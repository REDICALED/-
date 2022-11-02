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
        // EOF인지?
		
		// 이전 캐릭터가 operator의 일부가 될 가능성이 있고, 현재 캐릭터가
		// 따옴표도 아니고, 이전 operator에 붙여지면 그 두개를 합친다.
		
		// 이전 캐릭터가 operator의 일부가 될 가능성이 있고,
		// 현재 캐릭터가 그 뒤에 붙여지지 않으면, 구분한다.
		
		// 따옴표이면, 따옴표 나올때까지 한 덩어리.
		
		// $이면, 캐릭터 알파벳 아닌거 나올때까지 $의 일부로 처리
		
		// 현재 문자가 operator의 가능성이 있으면, 토큰 하나로 구분이 된다.
		// 다음 문자는 현재 문자의 operator에 합쳐질 수 있다.
		
		// 현재 문자가 공백이면, 무조건 구분해주고 현재 문자(블랭크) 삭제.
		
		// 현재 문자가 일반 char이고, 뒤에 문자와 연결되면 그 두개 합쳐라.
		
		// 현재 문자는 char 문자열의 시작 문자가 된다.
		
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
        else if (*line)
        {
            tokenize(line, &token_list);
        }
        free(line);
    }
    return (0);
}

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
#include "libft.h"

void	init_global(t_global *global, char *line)
{
	global->len = (int)ft_strlen(line);
	global->line = line;
	global->token_count = 0;
}

void    tokenize(char *line, t_global *global)
{
    int i;
    
    i = 0;
	init_global(global, line);
    while (1)
    {
		if (is_1(global, i))
			break ;
		if (is_2(global, i))
			break ;
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
        }
        free(line);
    }
    return (0);
}

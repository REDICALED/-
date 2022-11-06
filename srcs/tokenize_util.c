#include "minishell.h"

void	add_node(t_global *global, t_token token, char *str)
{
	t_node	*node;
	
	node = (t_node *)malloc(sizeof(t_node));
	node->token = token;
	node->str = ft_strdup(str);
	global->tail->next = node;
	node->next = NULL;
	node->prev = global->tail;
	global->tail = node;
}

void	init_global(t_global *global, char *line)
{
	t_node	*node;
	
	global->len = (int)ft_strlen(line);
	global->line = line;
	global->token_count = 0;
	node = (t_node *)malloc(sizeof(t_node));
	global->head = node;
	global->tail = node;
}

void    tokenize(char *line, t_global *global)
{
	int i;
	
	i = 0;
	init_global(global, line);
	while (1)
	{
		// EOF인지? 1
		if (count_1(global, i))
			break ;
			// 이전 캐릭터가 operator의 일부가 될 가능성이 있고, 현재 캐릭터가
			// 따옴표도 아니고, 이전 operator에 붙여지면 그 두개를 합친다. 2
		else if (count_2(global, i))
			i++;
			// 이전 캐릭터가 operator의 일부가 될 가능성이 있고,
			// 현재 캐릭터가 그 뒤에 붙여지지 않으면, 구분한다. 3
			// 따옴표이면, 따옴표 나올때까지 한 덩어리. 4 (후처리 부분을 위해서 메모를 해둬야댐)
		else if (count_4(global, &i))
			continue ;
			// $이면, 캐릭터 알파벳 아닌거 나올때까지 $의 일부로 처리 5
		else if (count_5(global, &i))
			continue ;
			// 현재 문자가 operator의 가능성이 있으면, 토큰 하나로 구분이 된다.
			// 다음 문자는 현재 문자의 operator에 합쳐질 수 있다. 6
		else if (count_6(global, i))
			i++;
			// 현재 문자가 공백이면, 무조건 구분해주고 현재 문자(블랭크) 삭제. 7
		else if (count_7(global, i))
			i++;
			// 현재 문자가 일반 char이고, 앞에 문자와 연결되면 그 두개 합쳐라. 8
		else if (count_8(global, i))
			i++;
		// 현재 문자는 char 문자열의 시작 문자가 된다. 9
		else if (count_9(global, i))
			i++;
	}
	t_node *node;
	
	node = global->tail;
	printf("token: %d, str: %s\n", node->token, node->str);
	node = node->next;
}

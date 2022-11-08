#include "minishell.h"

static void	pipe_mom_init(t_global *global)
{
	int		i;
	t_node	*node;

	i = -1;
	node = global->head;
	while (++i <= global->p_count)
	{
		global->p_arr[i].head = node;
		while (node->next && node->token != e_pipe)
			node = node->next;
		global->p_arr[i].tail = node;
		global->p_arr[i].pipe_error = 0;
		global->p_arr[i].pipe_func = 0;
		node = node->next;
		if (node == NULL)
			break ;
	}
	if (i++ < global->p_count)
	{
		global->p_arr[i].head = NULL;
		global->p_arr[i].tail = NULL;
		global->p_arr[i].pipe_error = 1;
		global->p_arr[i].pipe_func = 0;
	}
}

static void	hoo_init(t_global *global)
{
	t_node	*tmp;

	tmp = global->head;
	global->head = global->head->next;
	free(tmp);
	global->head->prev = NULL;
	global->p_arr = (t_p_mom *)malloc(sizeof(t_p_mom) * (global->p_count + 1));
	pipe_mom_init(global);
}

static void	hoo_token_check_loop(t_p_mom *p_mom, t_global *global)
{
	t_node	*node;

	node = p_mom->head;
	if (node == NULL)
	{
		printf("에러임\n");
		return ;
	}
	// ERROR 명세: e_error 토큰이 들어있는 노드를 방문할 시, 그 node의 str를 에러 메시지로 전해준다.
	while (node && node->prev != p_mom->tail)
	{
		//	1. here_doc 뒤에 d_quote, string, dollar -> s_quote로 변환 (해석을 안하므로)
		//	2. 오퍼레이터가 나오는지
		// 	3. /tmp/here_doc 에 임시 쓰기 파일이 저장되어 있음
		//	4. line 입력 받는 거 $해석 하는 것은 일단 나중에 ㄱㄱ
		if (node->token == read_in2)
			hoo_here_doc(node);
		// 1. 없는 환경변수의 경우 ""로 변환함
		// 2. 있는 환경변수의 경우 해석해줌
		if (node->token == dollar)
			hoo_dollar(node, global);
		/*
		if (node->token == s_quote)
			a;
		if (node->token == d_quote)
			a;
		if (node->token == read_in)
			a;
		if (node->token == read_out)
			a;
		if (node->token == read_out2)
			a;
		if (node->token == e_pipe)
			pipe_error 1 올려줌;
		1. built in?
		2. access() 되는가? (그냥 넣기)
		3. path 붙여가면서 access()
		4. 일반 string
		if (node->token == string)
			a;
		*/
		if (node->token == e_error)
			printf("---- Error at [-%s-] ----\n", node->str);
		node = node->next;
	}
}

static void	hoo_token_check(t_global *global)
{
	int		i;

	i = -1;
	while (++i <= global->p_count)
		hoo_token_check_loop(&(global->p_arr[i]), global);
}

/*
파이프 단위의 에러도 전체 에러와 같이 봄. (하지만 히어독은 실행함)
모든 인풋 리다이렉션, 히어독은 가장 마지막에 나온 것을 인풋으로 한다. dup2로 덮어씌워짐
히어독은 tmp에 파일 만들어서 덮어쓰고, 나중에 open 후 dup2 로 가져온다.
*/
void	hoo(t_global *global)
{
	hoo_init(global);
	hoo_token_check(global);
}

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

static int	hoo_token_check_loop(t_p_mom *p_mom, t_global *global)
{
	t_node	*node;

	node = p_mom->head;
	if (node == NULL)
	{
		printf("p_mom의 head가 NULL인 상황 -> 어떻게 처리할까??\n");
		return (1);
	}
	// ERROR 명세: e_error 토큰이 들어있는 노드를 방문할 시, 그 node의 str를 에러 메시지로 전해준다.
	while (node && node != p_mom->tail->next)
	{
		//1. 다음 노드가 NULL이면 error
		//2. 다음 노드가 공백인데, 공백 다음 노드가 NULL이면 error
		//3. 공백 있으면 제거 후, 공백 다음 노드와 현재 노드를 이어줌
		//4. 다음 노드가 오퍼레이터면 error
		//5. here_doc 시작 -> /tmp/here_doc에 해석된 내용을 해석 저장
		//6. read_in2 토큰을 read_in으로, LIMITER 노드의 토근을 string으로 변경
		if (node->token == read_in2)
			hoo_here_doc(node, global);
		//1. 토큰을 string을 변경
		//2. 그냥 $ 하나면 넘어가기
		//3. $?의 경우 g_exit_code로 변경
		//4. 있는 환경변수의 경우 해석한 문자열로 변경
		//5. 없는 환경변수의 경우 빈 문자열로 변경
		if (node->token == dollar)
			hoo_dollar(node, global);
		//1. single quote 일 때 하는게 없다. 토큰을 string으로 변경
		if (node->token == s_quote)
			node->token = string;
		//1. 문자열 안에 해석할 내용이 있다면 싹다 해석
		//2. 토큰을 string을 변경
		if (node->token == d_quote)
			hoo_double_quote(node, global);
		/*
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
		{
			printf("---- Error at [-%s-] ----\n", node->str);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

static void	hoo_token_check(t_global *global)
{
	int		i;

	i = -1;
	while (++i <= global->p_count)
	{
		if (hoo_token_check_loop(&(global->p_arr[i]), global))
			break ;
	}
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

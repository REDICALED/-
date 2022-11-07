#include "minishell.h"

void	pipe_mom_init(t_global *global)
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

void	hoo_init(t_global *global)
{
	t_node	*tmp;

	tmp = global->head;
	global->head = global->head->next;
	free(tmp);
	global->head->prev = NULL;
	global->p_arr = (t_p_mom *)malloc(sizeof(t_p_mom) * (global->p_count + 1));
	pipe_mom_init(global);
}

void	hoo_token_check_loop(t_node *node)
{
//	here_doc? 거의 goat 먼저 조지기
//	1. 뒤에 d_quote, string, dollar -> s_quote로 변환 (해석을 안하므로)
//	2. 오퍼레이터가 나오는지
	if (node->token == read_in2)
		hoo_here_doc(node);
//	1. built in?
//			 2. access() 되는가? (그냥 넣기)
//	3. path 붙여가면서 access()
//	4. 일반 string
/*
	else if (node->token == string)
		a;
	else if (node->token == dollar)
		a;
	else if (node->token == s_quote)
		a;
	else if (node->token == d_quote)
		a;
	else if (node->token == read_in)
		a;
	else if (node->token == read_out)
		a;
	else if (node->token == read_out2)
		a;
	else if (node->token == e_pipe)
		a;
	else if (node->token == e_pipe)
		pipe_error 1 올려줌;
*/
}

void	hoo_token_check(t_global *global)
{
	t_node	*node;
	int		i;
	
	i = -1;
	while (++i <= global->p_count)
	{
		node = global->p_arr[i].head;
		while (node->next && node->token != e_pipe)
		{
			hoo_token_check_loop(node);
			node = node->next;
		}
		node = node->next;
		if (node == NULL)
			break ;
	}
}

void	hoo(t_global *global)
{
	hoo_init(global);
	hoo_token_check(global);
}
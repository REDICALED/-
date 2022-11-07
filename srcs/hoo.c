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
		//현재 노드가 널이거나,
		while (node && node->token != e_pipe)
			node = node->next;
		global->p_arr[i].tail = node;
		global->p_arr[i].got_error = 0;
		global->p_arr[i].got_func = 0;
		if (node && node->token == e_pipe)
			node = node->next;
		else
			break;
	}
}

void	hoo_token_check(t_global *global)
{
	t_node	*node;
	int		i;
	
	
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
void	hoo(t_global *global)
{
	hoo_init(global);
	hoo_token_check(global);
}
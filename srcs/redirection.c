#include "minishell.h"

/*
read_in     -> operator와 string을 보고 실행되는 건지 확인.
				가장 마지막 것만 인풋으로 넣음
read_out    ->
read_out2   ->
*/

static void	input_loop(t_node *node, t_p_mom *p_mom)
{
	int		fd;

    fd = -1;
    if (p_mom->input != -1)
        close(p_mom->input);
    fd = open(node->next->str, O_RDONLY);
    if (fd == -1)
    {
        close(p_mom->input);
        if (p_mom->output != -1)
            close(p_mom->output);
        p_mom->input = -1;
        p_mom->output = -1;
        p_mom->read_error = 1;
        return ;
    }
    p_mom->input = fd;
}

static void	output_loop(t_node *node, t_p_mom *p_mom)
{
	int		fd;

    fd = -1;
	if (p_mom->output != -1)
		close(p_mom->output);
	if (node->token == read_out)
		fd = open(node->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token == read_out2)
		fd = open(node->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
        if (p_mom->input != -1)
            close(p_mom->input);
		close(p_mom->output);
        p_mom->input = -1;
		p_mom->output = -1;
		p_mom->read_error = 1;
		return ;
	}
	p_mom->output = fd;
}

void	redirection(t_global *global)
{
	int		i;
    t_node  *node;

	printf("redi start\n");
	i = -1;
	while (++i <= global->p_count)
	{
		node = global->p_arr[i].head;
        while(node && node != global->p_arr[i].tail->next)
		{
            if (node->token == read_in)
                input_loop(node, &(global->p_arr[i]));
			if (node->token == read_out || node->token == read_out2)
                output_loop(node, &(global->p_arr[i]));
			if (global->p_arr[i].read_error == 1)
                break ;
            node = node->next;
        }
	}
}

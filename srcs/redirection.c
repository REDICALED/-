#include "minishell.h"

/*
read_in     -> operator와 string을 보고 실행되는 건지 확인.
                가장 마지막 것만 인풋으로 넣음
read_out    ->
read_out2   ->
*/

static void	input_loop(t_p_mom *p_mom)
{
	t_node  *node;
    int     fd;

    node = p_mom->head;
	while (node && node != p_mom->tail->next)
    {
        if (node->token == read_in)
        {
            if (p_mom->input > -1)
                close(p_mom->input);
            // 0777? 어처피 안먹음.
            fd = open(node->next->str, O_RDONLY);
            printf("this is fd: %d\n", fd);
            if (fd == -1)
            {
                close(p_mom->input);
                p_mom->input = -1;
                p_mom->input_error = 1;
                return ;
            }
            p_mom->input = fd;
        }
        node = node->next;
    }
}

void	redirection(t_global *global)
{
    int i;

    printf("redi start\n");
    i = -1;
	while (++i <= global->p_count)
	{
        input_loop(&(global->p_arr[i]));
        //output_loop(&(global->p_arr[i]));
	}
}

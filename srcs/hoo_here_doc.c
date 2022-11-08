#include "minishell.h"

// here_doc LIMITER는 single quote 처리
// 하지만 here_doc 안에서 입력 받는 애들은 $ 확장하기
void    hoo_here_doc(t_node *node)
{
    printf("------------hoo_here_doc start\n");
    printf("str: %s\n", node->str);
    node = node->next;
    if (node == NULL)
        node->token = e_error;
    else
    {
        if (node->token == space)
        {
            node = node->next;
            if (node == NULL)
            {
                node->token = e_error;
                return ;
            }
        }
        if (node->token == e_pipe)
            node->token = e_error;
        else if (node->token == string || node->token == dollar || \
            node->token == d_quote)
        {
            node->token = s_quote;
        }
    }
    printf("------------hoo_here_doc end\n");
}


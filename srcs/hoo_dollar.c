#include "minishell.h"

void	hoo_dollar(t_node *node, t_global *global)
{
	printf("=== dollar start === \nstr: %s\n", node->str);
	(void)global;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:36:12 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/01 18:52:06 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token_list(t_global_list *token_list)
{
	token_list->len = 0;
	token_list->head = NULL;
	token_list->tail = NULL;
}

/*
void	push_left(t_stack *stack, int num)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->num = num;
	new->prev = NULL;
	if (stack->len == 0)
	{
		new->next = NULL;
		stack->head = new;
		stack->tail = new;
	}
	else
	{
		new->next = stack->head;
		stack->head->prev = new;
		stack->head = new;
	}
	stack->len++;
}
*/

void	push(t_stack *stack, int num)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->num = num;
	new->next = NULL;
	if (stack->len == 0)
	{
		new->prev = NULL;
		stack->head = new;
		stack->tail = new;
	}
	else
	{
		stack->tail->next = new;
		new->prev = stack->tail;
		stack->tail = new;
	}
	stack->len++;
}

/*
int	pop_left(t_stack *stack)
{
	t_node	*tmp;
	int		n;

	tmp = stack->head;
	n = tmp->num;
	stack->head = stack->head->next;
	if (stack->len == 1)
		stack->tail = stack->head;
	else
		stack->head->prev = NULL;
	stack->len--;
	free(tmp);
	return (n);
}
*/

int	pop(t_stack *stack)
{
	t_node	*tmp;
	int		n;

	tmp = stack->tail;
	n = tmp->num;
	if (stack->len == 1)
	{
		stack->tail = NULL;
		stack->head = NULL;
	}
	else
	{
		tmp->prev->next = NULL;
		stack->tail = tmp->prev;
	}
	stack->len--;
	free(tmp);
	return (n);
}

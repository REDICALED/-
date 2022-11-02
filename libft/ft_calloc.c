/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:10:53 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/18 23:16:58 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //size_t, malloc, bzero

void	*ft_calloc(size_t number, size_t size)
{
	void	*ans;

	ans = (void *)malloc(number * size);
	if (!ans)
		return (NULL);
	else
		ft_bzero(ans, number * size);
	return (ans);
}

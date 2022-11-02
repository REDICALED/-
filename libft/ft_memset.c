/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:36:41 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/08 18:19:13 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //size_t

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*un_b;
	unsigned char	un_c;

	un_c = (unsigned char)c;
	un_b = (unsigned char *)b;
	while (len > 0)
	{
		*un_b = un_c;
		len --;
		un_b ++;
	}
	return (b);
}

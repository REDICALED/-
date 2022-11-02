/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:22:11 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/15 18:32:35 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*un_dst;
	unsigned char	*un_src;

	un_dst = (unsigned char *)dst;
	un_src = (unsigned char *)src;
	if (!dst && !src && n != 0)
		return (0);
	while (n > 0)
	{
		*(un_dst++) = *(un_src++);
		n --;
	}
	return (dst);
}

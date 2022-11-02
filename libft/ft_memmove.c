/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:25:13 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/15 18:33:53 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //size_t, memcpy

void	*ft_memmove(void *dst,	const void *src, size_t	len)
{
	unsigned char	*un_dst;
	unsigned char	*un_src;

	un_dst = (unsigned char *)dst;
	un_src = (unsigned char *)src;
	if (!dst && !src && len != 0)
		return (0);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
		{
			*(un_dst + len) = *(un_src + len);
		}
	}
	return (dst);
}

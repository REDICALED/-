/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:04:32 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/07 20:11:54 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //size_t

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*un_s;
	unsigned char	un_c;

	un_s = (unsigned char *)s;
	un_c = (unsigned char)c;
	while (n--)
	{
		if (*(un_s++) == un_c)
		{
			return (--un_s);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:06:00 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/07 18:06:26 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //size_t

void	ft_bzero(void	*s, size_t n)
{
	unsigned char	*un_s;

	un_s = (unsigned char *)s;
	while (n--)
		*(un_s++) = 0;
}

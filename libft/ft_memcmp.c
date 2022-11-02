/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:53:12 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/07 20:58:54 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //size_t

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*unc_s1;
	unsigned char	*unc_s2;

	unc_s1 = (unsigned char *)s1;
	unc_s2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (--n && *unc_s1 == *unc_s2)
	{
		unc_s1++;
		unc_s2++;
	}
	return ((int)(*unc_s1 - *unc_s2));
}

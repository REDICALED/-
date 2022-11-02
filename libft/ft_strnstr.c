/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:22:22 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/15 19:26:11 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int			j;
	size_t		count;
	const char	*oghay;

	oghay = haystack;
	count = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && count < len)
	{
		while (*(haystack + j) == *(needle + j) && *(haystack + j) != '\0' \
				&& count < len)
		{
			j++;
			count++;
		}
		if (*(needle + j) == '\0')
			return ((char *)haystack);
		haystack++;
		count = haystack - oghay;
		j = 0;
	}
	return (0);
}

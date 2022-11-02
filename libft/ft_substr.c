/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:20:38 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/19 03:21:27 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //malloc

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
		len = 0;
	if (ft_strlen(s) <= len)
		len = ft_strlen(s);
	sub_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub_s)
		return (0);
	while (i < len && *(s + start + i) != '\0')
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

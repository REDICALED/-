/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:03:34 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/15 18:38:50 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && (s1[i] == s2[i]))
	{
		if (!s1[i] || !s2[i])
			return (0);
		i ++;
	}
	if (s1[i] != s2[i] && len != i)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

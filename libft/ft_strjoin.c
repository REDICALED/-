/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:17:24 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/18 18:43:18 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //malloc, strlen

void	be0(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*ans;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	ans = (char *)malloc(sizeof(*s1) * (len + 1));
	if (!ans)
		return (0);
	be0(&i, &j);
	while (*(s1 + i) != '\0')
	{
		*(ans + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j) != '\0')
	{
		*(ans + i) = *(s2 + j);
		i++;
		j++;
	}
	*(ans + i) = '\0';
	return (ans);
}

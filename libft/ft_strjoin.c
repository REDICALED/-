/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:17:24 by byeonkim          #+#    #+#             */
/*   Updated: 2022/11/10 03:14:01 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //malloc, strlen

void	be0(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*ft_strjoin(char *s1, char s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*ans;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + 1;
	ans = (char *)malloc(sizeof(*s1) * (len + 1));
	if (!ans)
		return (0);
	be0(&i, &j);
	while (*(s1 + i) != '\0')
	{
		*(ans + i) = *(s1 + i);
		i++;
	}
	*(ans + i) = s2;
	i++;
	*(ans + i) = '\0';
	free(s1);
	return (ans);
}

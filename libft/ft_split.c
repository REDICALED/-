/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:25:30 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/20 18:11:27 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	counter(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s)
	{
		if (*s != c)
		{
			num++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (num);
}

size_t	notc_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char	**split_free(char **split, size_t i)
{
	while (i)
	{
		free(*(split + i));
		*(split + i) = NULL;
		i--;
	}
	free(*split);
	*split = NULL;
	free(split);
	split = NULL;
	return (NULL);
}

char	**ans_split(char	**ans, char const *s, char c, size_t len_size)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (len_size)
	{
		len = notc_len(s, c);
		ans[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!ans[i])
			return (split_free(ans, i));
		while (*s == c)
			s++;
		ft_strlcpy (ans[i], s, len + 1);
		s = s + len;
		i++;
		len_size --;
	}
	ans[i] = NULL;
	return (ans);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	size_t	len_size;

	if (!s)
		return (NULL);
	len_size = counter(s, c);
	ans = (char **)malloc(sizeof(char *) * (len_size + 1));
	if (!ans)
		return (NULL);
	ans = ans_split(ans, s, c, len_size);
	return (ans);
}

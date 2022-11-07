/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:38:34 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/18 18:44:13 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //malloc, strlen

size_t	len_count(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr((set), *(s1 + len - 1)) != 0)
		len --;
	if (len == 0)
		return (0);
	while (len > 0 && ft_strchr((set), *(s1 + i)) != 0)
	{
		len --;
		i ++;
	}
	return (len);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*ans;
	size_t	len;
	size_t	i;

	if (!s1 || !set)
		return (0);
	i = 0;
	len = len_count(s1, set);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (0);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != 0)
		i++;
	ft_strlcpy(ans, s1 + i, len + 1);
	free(s1);
	return (ans);
}

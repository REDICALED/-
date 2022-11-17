/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:24:12 by byeonkim          #+#    #+#             */
/*   Updated: 2022/11/12 06:39:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	while (*(s))
	{
		if (*(s) == char_c)
			return ((char *)(s));
		s++;
	}
	if (char_c == '\0')
		return ((char *)s);
	return (0);
}

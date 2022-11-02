/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:24:12 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/12 17:53:12 by byeonkim         ###   ########.fr       */
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

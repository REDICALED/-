/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:49:16 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/05 17:01:55 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*zuso;
	char		char_c;

	char_c = (char)c;
	zuso = s;
	while (*s != '\0')
		s++;
	if (char_c == '\0')
		return ((char *)s);
	while (s >= zuso)
	{
		if (*s == char_c)
			return ((char *)s);
		s--;
	}
	return (0);
}

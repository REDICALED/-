/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:36:44 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/15 19:54:27 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //malloc

int	what_buho(int n)
{
	if (n >= 0)
		return (n);
	else
		return (-1 * n);
}

int	int_len(int tmp)
{
	int	i;

	i = 0;
	while (tmp != 0)
	{
		tmp = tmp / 10;
		i ++;
	}
	return (i);
}

char	*zero_min(int n)
{
	char	*ans;

	if (n == -2147483648)
	{
		ans = (char *)malloc(sizeof(char) * 12);
		if (!ans)
			return (0);
		ft_strlcpy(ans, "-2147483648", 12);
	}
	else
	{
		ans = (char *)malloc(sizeof(char) * 2);
		if (!ans)
			return (0);
		ft_strlcpy(ans, "0", 2);
	}
	return (ans);
}

char	*ans_gen(char *ans, int len, int tmp, int n)
{
	int	last_len;

	last_len = len;
	while (tmp != 0)
	{
		*(ans + len - 1) = tmp % 10 + 48;
		tmp = tmp / 10;
		len --;
	}
	*(ans + last_len) = '\0';
	if (n < 0)
		ans --;
	return (ans);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ans;
	int		tmp;

	len = 0;
	if (n == -2147483648 || n == 0)
		return (zero_min(n));
	tmp = what_buho(n);
	len = int_len(tmp);
	if (n > 0)
		ans = (char *)malloc(sizeof(char) * (len + 1));
	else
		ans = (char *)malloc(sizeof(char) * (len + 2));
	if (!ans)
		return (0);
	if (n < 0)
	{
		ans[0] = '-';
		ans ++;
	}
	ans = ans_gen(ans, len, tmp, n);
	return (ans);
}

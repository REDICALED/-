/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:43:01 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/15 20:59:51 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //unistd

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	ans[10];
	long	long_n;

	long_n = (long) n;
	i = 9;
	if (n < 0)
	{
		write(fd, "-", 1);
		long_n = long_n * -1;
	}
	while (long_n != 0)
	{
		ans[i] = long_n % 10 + 48;
		long_n = long_n / 10;
		i --;
	}
	i++;
	while (i < 10)
	{
		write(fd, ans + i, 1);
		i ++;
	}
	if (n == 0)
		write(fd, "0", 1);
}

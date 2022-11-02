/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeonkim <byeonkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:06:28 by byeonkim          #+#    #+#             */
/*   Updated: 2022/04/08 18:59:25 by byeonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long long	ans;
	unsigned long long	max;
	int					flag;

	ans = 0;
	flag = 1;
	max = 9223372036854775807;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		flag *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		ans = (ans * 10) + (*str - '0');
		if (flag == 1 && ans > max)
			return (-1);
		if (flag == -1 && ans > max + 1)
			return (0);
		str++;
	}
	return (ans * flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:34:07 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/06 16:03:29 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_time(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, 0) < 0)
	{
		ft_error("Time not received");
		return (-1);
	}
	return (timeval.tv_sec * 1000 + (timeval.tv_usec / 1000));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	char *radix;

	radix = "0123456789";
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(radix[n % 10]);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if ((s1 && !s2) || (!s1 && s2))
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	else
		write(1, "(null)", 6);
}

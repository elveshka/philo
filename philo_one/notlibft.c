/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notlibft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:11 by esnowbal          #+#    #+#             */
/*   Updated: 2021/01/29 14:44:44 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			not_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}

int			not_atoi(const char *str)
{
	int res;

	res = 0;
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - 48;
		str++;
	}
	return (res);
}

int			puterr(void)
{
	printf("Invalid argument\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notlibft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:11 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/11 13:43:50 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			not_strlen(char *s)
{
	int r;

	r = 0;
	while (s[r++])
		;
	return (r);
}

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

void		*not_calloc(size_t count, size_t cell_size)
{
	void	*res;

	if (cell_size != 0)
		if (((count * cell_size) / cell_size) != count)
			return (NULL);
	if (count * cell_size == 0)
		return (malloc(0));
	if (!(res = malloc(cell_size * count)))
		return (NULL);
	memset(res, 0, count * cell_size);
	return (res);
}

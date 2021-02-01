/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/01 22:16:21 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			eating(int i)
{
	printf("%d is eating\n", i + 1);
}

void			sleeping(int i)
{
	printf("%d is sleeping\n", i + 1);
}

void			thinking(int i)
{
	printf("%d is thinking\n", i + 1);
}

void			grabbing_forks(int i)
{
	printf("%d has taken a fork\n", i + 1);
}

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/02 20:37:02 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			eating(t_phil *phil)
{
	printf("%lu %d is eating\n", get_time() - phil->living_time, phil->index + 1);
	usleep(200000);
}

void			sleeping(t_phil *phil)
{
	printf("%lu %d is sleeping\n", get_time() - phil->living_time, phil->index + 1);
}

void			thinking(t_phil *phil)
{
	printf("%lu %d is thinking\n", get_time() - phil->living_time, phil->index + 1);
}

void			grabbing_forks(t_phil *phil)
{
	printf("%lu %d has taken a fork\n", get_time() - phil->living_time, phil->index + 1);
}

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

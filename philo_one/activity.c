/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/05 13:17:10 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			eating(t_phil *phil)
{
	unsigned long		time;

	phil->living_time = get_time();
	time = phil->data->time_to_eat * 990;
	usleep(time);
	while (get_time() - phil->living_time - time < (unsigned long)phil->data->time_to_eat * 1000)
		usleep(10);
	phil->living_time = get_time();
	printf("%lu %d is eating\n",
	phil->living_time - phil->start_time, phil->index + 1);
}

void			sleeping(t_phil *phil)
{
	unsigned long		time;

	phil->living_time = get_time();
	time = phil->data->time_to_sleep * 990;
	usleep(time);
	while (get_time() - phil->living_time - time < (unsigned long)phil->data->time_to_eat * 1000)
		usleep(10);
	phil->living_time = get_time();
	printf("%lu %d is sleeping\n",
	phil->living_time - phil->start_time, phil->index + 1);
}

void			thinking(t_phil *phil)
{
	printf("%lu %d is thinking\n",
	get_time() - phil->living_time, phil->index + 1);
}

void			grabbing_forks(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%lu %d has taken a fork\n",
	phil->living_time - phil->start_time, phil->index + 1);
}

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

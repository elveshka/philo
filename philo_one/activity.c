/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/10 13:52:02 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			eating(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%ld %d is eating\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	while (get_time() < phil->living_time + phil->data->time_to_eat)
		usleep(100);
	phil->living_time = get_time();
}

void			sleeping(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%ld %d is sleeping\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	while (get_time() < phil->living_time + phil->data->time_to_sleep)
		usleep(100);
	phil->living_time = get_time();
}

void			thinking(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%ld %d is thinking\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	while (get_time() < phil->living_time + phil->data->time_to_die - \
	phil->data->time_to_eat - phil->data->time_to_sleep)
		usleep(100);
	phil->living_time = get_time();
}

void			grabbing_forks(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%ld %d has taken a fork\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
}

long			get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

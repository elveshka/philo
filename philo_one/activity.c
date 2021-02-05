/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/05 16:27:13 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			eating(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%d %d is eating\n",
	phil->living_time - phil->start_time, phil->index + 1);
	while (get_time() < phil->last_action + phil->data->time_to_eat)
		usleep(100);
	phil->living_time = get_time();
	phil->last_action = phil->living_time;
}

void			sleeping(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%d %d is sleeping\n",
	phil->living_time - phil->start_time, phil->index + 1);
	while (get_time() < phil->last_action + phil->data->time_to_sleep)
		usleep(100);
	phil->living_time = get_time();
	phil->last_action = phil->living_time;
}

void			thinking(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%d %d is thinking\n",
	phil->living_time - phil->start_time, phil->index + 1);
	while (get_time() < phil->last_action + phil->data->time_to_die)
		usleep(100);
	phil->living_time = get_time();
	phil->last_action = phil->living_time;
}

void			grabbing_forks(t_phil *phil)
{
	phil->living_time = get_time();
	printf("%d %d has taken a fork\n",
	phil->living_time - phil->start_time, phil->index + 1);
}

int				get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/13 16:40:03 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			waste_of_time(int time_to_waste)
{
	long		start;

	start = get_time();
	while (get_time() - start < time_to_waste)
		usleep(100);
}

int				eating(t_phil *phil)
{
	grabbing_forks(phil);
	phil->start_meal = get_time();
	pthread_mutex_lock(phil->print);
	printf("%ld %d is eating\n",
	phil->start_meal - phil->data->start_time, phil->index + 1);
	pthread_mutex_unlock(phil->print);
	waste_of_time(phil->data->time_to_eat);
	pthread_mutex_unlock(phil->right);
	pthread_mutex_unlock(phil->left);
	phil->meal_times--;
	if (phil->meal_times == 0)
		return (1);
	return (0);
}

void			sleeping(t_phil *phil)
{
	pthread_mutex_lock(phil->print);
	printf("%ld %d is sleeping\n",
	get_time() - phil->data->start_time, phil->index + 1);
	pthread_mutex_unlock(phil->print);
	waste_of_time(phil->data->time_to_sleep);
}

void			thinking(t_phil *phil)
{
	pthread_mutex_lock(phil->print);
	printf("%ld %d is thinking\n",
	get_time() - phil->data->start_time, phil->index + 1);
	pthread_mutex_unlock(phil->print);
}

void			grabbing_forks(t_phil *phil)
{
	pthread_mutex_lock(phil->left);
	pthread_mutex_lock(phil->print);
	printf("%ld %d has taken a fork\n",
	get_time() - phil->data->start_time, phil->index + 1);
	pthread_mutex_unlock(phil->print);
	pthread_mutex_lock(phil->right);
	pthread_mutex_lock(phil->print);
	printf("%ld %d has taken a fork\n",
	get_time() - phil->data->start_time, phil->index + 1);
	pthread_mutex_unlock(phil->print);
}

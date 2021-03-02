/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:06:18 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/02 15:51:25 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			waste_of_time(int time_to_waste, t_phil *phil)
{
	long		start;

	start = get_time();
	while (get_time() - start < time_to_waste)
	{
		usleep(10);
		phil->living_time = get_time();
		if (phil->living_time - phil->start_meal > phil->data->time_to_die)
		{
			phil->died++;
			return ;
		}
	}
}

int				eating(t_phil *phil)
{
	if (grabbing_forks(phil))
		return (1);
	phil->start_meal = get_time();
	sem_wait(phil->print);
	printf("%ld %d is eating\n",
	phil->start_meal - phil->data->start_time, phil->index + 1);
	sem_post(phil->print);
	waste_of_time(phil->data->time_to_eat, phil);
	sem_post(phil->forks);
	sem_post(phil->forks);
	phil->meal_times--;
	if (phil->meal_times == 0)
		return (2);
	phil->living_time = get_time();
	return (0);
}

int				sleeping(t_phil *phil)
{
	if ((phil->living_time = get_time()) - phil->start_meal > \
	phil->data->time_to_die)
		return (1);
	sem_wait(phil->print);
	printf("%ld %d is sleeping\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	sem_post(phil->print);
	waste_of_time(phil->data->time_to_sleep, phil);
	return (0);
}

int				thinking(t_phil *phil)
{
	if ((phil->living_time = get_time()) - phil->start_meal > \
	phil->data->time_to_die)
		return (1);
	sem_wait(phil->print);
	printf("%ld %d is thinking\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	sem_post(phil->print);
	return (0);
}

int				grabbing_forks(t_phil *phil)
{
	sem_wait(phil->forks);
	if (((phil->living_time = get_time()) - phil->start_meal > \
	phil->data->time_to_die) && phil->start_meal != 0)
		return (1);
	sem_wait(phil->print);
	printf("%ld %d has taken a fork\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	sem_post(phil->print);
	sem_wait(phil->forks);
	if (((phil->living_time = get_time()) - phil->start_meal > \
	phil->data->time_to_die) && phil->start_meal != 0)
		return (1);
	phil->living_time = get_time();
	sem_wait(phil->print);
	printf("%ld %d has taken a fork\n",
	phil->living_time - phil->data->start_time, phil->index + 1);
	sem_post(phil->print);
	return (0);
}

long			get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

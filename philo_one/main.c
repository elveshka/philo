/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/26 20:09:23 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				*phillip(void *phil)
{
	int		res;

	while (((t_phil *)phil)->meal_times)
	{
		if ((res = eating((t_phil *)phil)))
		{
			if (res == 1)
				((t_phil *)phil)->died++;
			break ;
		}
		if (sleeping((t_phil *)phil) || thinking((t_phil *)phil))
		{
			((t_phil *)phil)->died++;
			break ;
		}
	}
	if (((t_phil *)phil)->died)
	{
		pthread_mutex_lock(((t_phil *)phil)->print);
		printf("%ld %d died\n", get_time() - \
		((t_phil *)phil)->data->start_time, ((t_phil *)phil)->index + 1);
	}
	return (NULL);
}

void				simulation(t_data *data, t_phil *philos)
{
	int		i;
	int		meals;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num)
	{
		pthread_create(&(data->threads[i]), NULL, phillip, (void*)&(philos[i]));
		usleep(250);
	}
	i = -1;
	meals = 0;
	while (++i < data->num)
	{
		if ((philos + i)->died)
			break ;
		meals += (philos + i)->meal_times;
		if (i == data->num - 1)
		{
			if (meals == 0)
				break ;
			else
				meals = 0;
			i = -1;
		}
	}
	usleep(500);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	int				i;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*print;

	if (philo_config(ac, av, &data))
		return (puterr());
	forks = create_mutex(data.num);
	data.threads = malloc(sizeof(pthread_t) * data.num);
	print = malloc(sizeof(pthread_mutex_t));
	philos = philos_init(&data, forks, print);
	simulation(&data, philos);
	i = -1;
	while (++i < data.num)
		pthread_mutex_destroy(forks[i]);
	pthread_mutex_destroy(print);
	while (--i >= 0)
		free(forks[i]);
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	free(forks);
	free(data.threads);
	free(philos);
	return (0);
}

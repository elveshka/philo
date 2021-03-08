/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/08 12:23:34 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			*phillip(void *phil)
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
		if (get_time() - ((t_phil *)phil)->data->start_time < 1000000000)
			printf("%ld %d died\n", get_time() - \
			((t_phil *)phil)->data->start_time, ((t_phil *)phil)->index + 1);
	}
	return (NULL);
}

static void			simulation(t_data *data, t_phil *philos, int i)
{
	int		meals;

	data->start_time = get_time();
	while (++i < data->num)
	{
		pthread_create(&(data->threads[i]), NULL, phillip, (void*)&(philos[i]));
		usleep(250);
	}
	meals = 0;
	while (--i >= 0)
	{
		if ((philos + i)->died)
			break ;
		meals += (philos + i)->meal_times;
		if (i == 0)
		{
			if (meals == 0)
				break ;
			else
				meals = 0;
			i = data->num;
		}
	}
	if ((philos + i)->died)
		pthread_join(data->threads[i], NULL);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	int				i;
	pthread_mutex_t	**forks;
	pthread_mutex_t	print;

	if (philo_config(ac, av, &data))
		return (puterr());
	forks = create_mutex(data.num);
	data.threads = malloc(sizeof(pthread_t) * data.num);
	philos = philos_init(&data, forks, &print);
	i = -1;
	simulation(&data, philos, i);
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	while (--i >= 0)
		pthread_mutex_destroy(forks[i]);
	while (++i < data.num)
		free(forks[i]);
	free(forks);
	free(data.threads);
	free(philos);
	pthread_mutex_destroy(&print);
	return (0);
}

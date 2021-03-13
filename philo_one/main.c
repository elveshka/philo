/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/13 16:41:18 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			killer(t_phil *phil)
{
	if (get_time() - phil->start_meal > phil->data->time_to_die)
	{
		pthread_mutex_lock(phil->print);
		printf("%ld %d died\n", get_time() - \
			phil->data->start_time, phil->index + 1);
		return (1);
	}
	return (0);
}

static void			*phillip(void *phil)
{
	while (((t_phil *)phil)->meal_times)
	{
		if (eating((t_phil *)phil))
			break ;
		sleeping((t_phil *)phil);
		thinking((t_phil *)phil);
	}
	return (NULL);
}

static void			simulation(t_data *data, t_phil *philos, int i)
{
	int		meals;

	while (++i < data->num)
	{
		philos[i].start_meal = get_time();
		pthread_create(&(data->threads[i]), NULL, phillip, (void*)&(philos[i]));
		usleep(250);
	}
	meals = 0;
	while (--i >= 0)
	{
		if (killer(&philos[i]))
			break ;
		meals += (&philos[i])->meal_times;
		if (i == 0)
		{
			if (meals == 0)
				break ;
			else
				meals = 0;
			i = data->num;
		}
		usleep(100);
	}
	usleep(500000);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	int				i;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

	if (philo_config(ac, av, &data))
		return (puterr());
	forks = create_mutex(data.num);
	data.threads = malloc(sizeof(pthread_t) * data.num);
	philos = philos_init(&data, forks, &print);
	i = -1;
	data.start_time = get_time();
	simulation(&data, philos, i);
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	while (++i < data.num)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
	free(data.threads);
	free(philos);
	return (0);
}

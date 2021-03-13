/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/13 16:52:17 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			killer(t_phil *phil)
{
	if (get_time() - phil->start_meal > phil->data->time_to_die)
	{
		sem_wait(phil->print);
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
	}
	i = -1;
	meals = 0;
	while (++i < data->num)
	{
		if (killer(&philos[i]))
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
		usleep(100);
	}
	usleep(500000);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	int				i;
	sem_t			*forks;
	sem_t			*print;

	if (philo_config(ac, av, &data))
		return (puterr());
	data.threads = malloc(sizeof(pthread_t) * data.num);
	sem_unlink("/forks");
	sem_unlink("/print");
	forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data.num);
	print = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);
	philos = philos_init(&data, &forks, print);
	i = -1;
	data.start_time = get_time();
	simulation(&data, philos, i);
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	sem_close(philos[0].waiter);
	free(data.threads);
	free(philos);
	sem_close(forks);
	sem_close(print);
	return (0);
}

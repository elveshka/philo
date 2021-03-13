/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/13 18:47:05 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			*killer(void *philo)
{
	t_phil		*phil;

	phil = (t_phil*)philo;
	while (1)
	{
		if (get_time() - phil->start_meal > phil->data->time_to_die)
		{
			sem_wait(phil->print);
			printf("%ld %d died\n", get_time() - \
				phil->data->start_time, phil->index + 1);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

static int			phillip2(t_phil *phil)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, killer, phil);
	while (((t_phil *)phil)->meal_times)
	{
		if (eating((t_phil *)phil))
			break ;
		sleeping((t_phil *)phil);
		thinking((t_phil *)phil);
	}
	pthread_detach(thread);
	return (2);
}

static void			*phillip(void *phil)
{
	int			res;
	pid_t		pid;

	if (((t_phil*)phil)->meal_times)
	{
		pid = fork();
		if (!pid)
			exit(phillip2((t_phil*)phil));
		waitpid(pid, &res, 0);
		if (WEXITSTATUS(res) == 1)
			((t_phil*)phil)->data->dead = 1;
		if (WEXITSTATUS(res) == 2)
			((t_phil*)phil)->meal_times = 0;
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
		if (data->dead)
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
	usleep(50000);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	sem_t			*forks;
	sem_t			*print;
	int				i;

	if (philo_config(ac, av, &data))
		return (puterr());
	data.threads = malloc(sizeof(pthread_t) * data.num);
	sem_unlink("/print");
	sem_unlink("/forks");
	forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data.num);
	print = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);
	philos = philos_init(&data, forks, print);
	i = -1;
	data.start_time = get_time();
	simulation(&data, philos, i);
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	sem_close(forks);
	sem_close(print);
	sem_close(philos[0].waiter);
	free(philos);
	free(data.threads);
	return (0);
}

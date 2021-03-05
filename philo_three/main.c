/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/05 18:56:30 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			phillip2(t_phil *phil)
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
			res = 1;
			break ;
		}
	}
	if (((t_phil *)phil)->died)
	{
		sem_wait(((t_phil *)phil)->print);
		printf("%ld %d died\n", get_time() - \
		((t_phil *)phil)->data->start_time, ((t_phil *)phil)->index + 1);
	}
	return (res);
}

static void			*phillip(void *phil)
{
	int		res;
	pid_t	pid;

	if (((t_phil*)phil)->meal_times)
	{
		pid = fork();
		if (!pid)
			exit(phillip2((t_phil*)phil));
		waitpid(pid, &res, 0);
		if (res == 256)
			((t_phil*)phil)->died++;
		if (res == 512)
			((t_phil*)phil)->meal_times = 0;
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
	sem_t			*forks;
	sem_t			*print;
	int				i;

	if (philo_config(ac, av, &data))
		return (puterr());
	data.threads = malloc(sizeof(pthread_t) * data.num);
	forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data.num);
	print = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);
	sem_unlink("/print");
	sem_unlink("/forks");
	philos = philos_init(&data, forks, print);
	i = -1;
	simulation(&data, philos, i);
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	sem_close(forks);
	sem_close(print);
	free(philos);
	free(data.threads);
	return (0);
}

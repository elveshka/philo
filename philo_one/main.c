/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/10 15:54:14 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				*phillip(void *phil)
{
	while (!((t_phil *)phil)->died)
	{
		pthread_mutex_lock(((t_phil *)phil)->left);
		grabbing_forks((t_phil *)phil);
		pthread_mutex_lock(((t_phil *)phil)->right);
		grabbing_forks((t_phil *)phil);
		if (eating((t_phil *)phil))
		{
			((t_phil *)phil)->died++;
			break ;
		}
		pthread_mutex_unlock(((t_phil *)phil)->right);
		pthread_mutex_unlock(((t_phil *)phil)->left);
		if (sleeping((t_phil *)phil) || thinking((t_phil *)phil))
		{
			((t_phil *)phil)->died++;
			break ;
		}
	}
	printf("%ld %d died\n", \
	((t_phil *)phil)->living_time - ((t_phil *)phil)->data->start_time, \
	((t_phil *)phil)->index + 1);
	return (NULL);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	int				i;
	pthread_mutex_t	**forks;

	(void)time;
	if (ac < 5 || ac > 6)
		return (puterr());
	if (philo_config(ac, av, &data))
		return (1);
	forks = create_mutex(data.num);
	data.threads = malloc(sizeof(pthread_t) * data.num);
	philos = philos_init(&data, forks);
	i = -1;
	while (++i < data.num)
	{
		pthread_create(&data.threads[i], NULL, phillip, (void*)&philos[i]);
		usleep(300);
	}
	getchar();
	i = -1;
	while (++i < data.num)
		if (philos[i].died)
			printf("%d is dead\n", i + 1);
	i = -1;
	while (++i < data.num)
		pthread_mutex_destroy(forks[i]);
	i = -1;
	while (++i < data.num)
		free(forks[i]);
	i = -1;
	while (++i < data.num)
		pthread_detach(data.threads[i]);
	free(forks);
	free(data.threads);
	free(philos);
	getchar();
	return (0);
}

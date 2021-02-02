/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/02 20:46:49 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				*sobaka(void *phil)
{
	pthread_mutex_lock(((t_phil *)phil)->left);
	pthread_mutex_lock(((t_phil *)phil)->right);
	grabbing_forks((t_phil *)phil);
	eating((t_phil *)phil);
	sleeping((t_phil *)phil);
	thinking((t_phil *)phil);
	printf("%d\n", ((t_phil *)phil)->index + 1);
	pthread_mutex_unlock(((t_phil *)phil)->right);
	pthread_mutex_unlock(((t_phil *)phil)->left);
	return (NULL);
}

int					main(int ac, char **av)
{
	t_data			data;
	t_phil			*philos;
	int				i;
	unsigned long	time;
	pthread_mutex_t	**forks;

	time = get_time();
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
		pthread_create(&data.threads[i], NULL, sobaka, (void*)&philos[i]);
		usleep(10);
	}
	getchar();
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
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/05 16:31:34 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				*sobaka(void *phil)
{
	while (!((t_phil *)phil)->died)
	{
		pthread_mutex_lock(((t_phil *)phil)->left);
		grabbing_forks((t_phil *)phil);
		pthread_mutex_lock(((t_phil *)phil)->right);
		grabbing_forks((t_phil *)phil);
		eating((t_phil *)phil);
		pthread_mutex_unlock(((t_phil *)phil)->right);
		pthread_mutex_unlock(((t_phil *)phil)->left);
		sleeping((t_phil *)phil);
		thinking((t_phil *)phil);
		if (((t_phil *)phil)->last_action > \
		((t_phil *)phil)->data->time_to_die + get_time())
			((t_phil *)phil)->died++;
	}
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
		pthread_create(&data.threads[i], NULL, sobaka, (void*)&philos[i]);
		usleep(100);
	}
	// getchar();
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

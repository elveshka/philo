/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/12 16:31:31 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				*phillip(void *phil)
{
	while (((t_phil *)phil)->meal_times)
	{
		if ((((t_phil *)phil)->living_time - ((t_phil *)phil)->start_meal > \
		((t_phil *)phil)->data->time_to_die))
		{
			((t_phil *)phil)->died++;
			break ;
		}
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
	if (((t_phil *)phil)->died)
	{
		pthread_mutex_lock(((t_phil *)phil)->print);
		printf("%ld %d died\n", \
		get_time() - ((t_phil *)phil)->data->start_time, \
		((t_phil *)phil)->index + 1);
	}
	return (NULL);
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
	i = -1;
	data.start_time = get_time();
	while (++i < data.num)
	{
		pthread_create(&data.threads[i], NULL, phillip, (void*)&philos[i]);
		usleep(150);
	}
	getchar();
	i = -1;
	while (++i < data.num)
		pthread_mutex_destroy(forks[i]);
	pthread_mutex_destroy(print);
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

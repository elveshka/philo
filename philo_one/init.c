/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:51:49 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/13 16:19:51 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil				*philos_init(t_data *data, pthread_mutex_t *forks, \
								pthread_mutex_t *print)
{
	t_phil		*philos;
	int			i;

	i = -1;
	philos = malloc(sizeof(t_phil) * data->num);
	pthread_mutex_init(print, NULL);
	while (++i < data->num)
	{
		philos[i].index = i;
		philos[i].data = data;
		philos[i].meal_times = data->num_eat != -1 ? data->num_eat : -1;
		philos[i].left = &forks[i];
		philos[i].right = &forks[(i + 1) % data->num];
		philos[i].print = print;
	}
	return (philos);
}

int					philo_config(int ac, char **av, t_data *data)
{
	int i;
	int j;

	if (ac < 5 || ac > 6)
		return (1);
	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!not_isdigit(av[i][j]))
				return (1);
			j++;
		}
	}
	data->num = not_atoi(av[1]);
	if (data->num < 2)
		return (1);
	data->time_to_die = not_atoi(av[2]);
	data->time_to_eat = not_atoi(av[3]);
	data->time_to_sleep = not_atoi(av[4]);
	data->num_eat = (ac == 6) ? not_atoi(av[5]) : -1;
	return (0);
}

pthread_mutex_t		*create_mutex(int num)
{
	int				i;
	pthread_mutex_t	*ret;

	i = -1;
	if (!(ret = not_calloc(num + 1, sizeof(pthread_mutex_t))))
		return (NULL);
	i = -1;
	while (++i < num)
		pthread_mutex_init(&ret[i], NULL);
	return (ret);
}

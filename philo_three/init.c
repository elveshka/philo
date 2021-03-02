/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:51:49 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/02 16:14:36 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil				*philos_init(t_data *data, sem_t **forks, sem_t *print)
{
	t_phil		*philos;
	int			i;

	i = -1;
	philos = malloc(sizeof(t_phil) * data->num);
	while (++i < data->num)
	{
		philos.died = 0;
		philos.living_time = data->time_to_die - 1;
		philos.start_meal = 0;
		philos.meal_times = data->num_eat != -1 ? data->num_eat : -1;
		philos.forks = *forks;
		philos.print = print;
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
				return (puterr());
			j++;
		}
	}
	data->num = not_atoi(av[1]);
	if (data->num < 2)
		return (puterr());
	data->time_to_die = not_atoi(av[2]);
	data->time_to_eat = not_atoi(av[3]);
	data->time_to_sleep = not_atoi(av[4]);
	data->num_eat = (ac == 6) ? not_atoi(av[5]) : -1;
	return (0);
}

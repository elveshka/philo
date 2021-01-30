/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/01/30 16:19:37 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*sobaka(void *ar)
{
	printf("ya sobaka, ty sobaka - %3d\n", *(int*)ar);

	return NULL;
}

int			main(int ac, char **av)
{
	pthread_t		*phil;
	t_phi_data		philos;
	int				i;
	int				j;

	if (ac < 5 || ac > 6)
		return (puterr());
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!not_isdigit(av[i][j]))
				return (puterr());
			j++;
		}
		i++;
	}
	philos.num = not_atoi(av[1]);
	if (philos.num < 2)
		return (puterr());
	philos.time_to_die = not_atoi(av[2]);
	philos.time_to_eat = not_atoi(av[3]);
	philos.time_to_sleep = not_atoi(av[4]);
	philos.num_eat = (ac == 6) ? not_atoi(av[5]) : -1;
	i = -1;
	phil = malloc(sizeof(pthread_t) * philos.num);
	while (++i < philos.num)
	{
		pthread_create(&phil[i], NULL, sobaka, (void*)&i);
	}
	usleep(1000000);
	return (0);
}

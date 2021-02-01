/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:52 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/01 21:57:12 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t		**forks;

pthread_mutex_t		**create_mutex(int num)
{
	int				i;
	pthread_mutex_t	**ret;

	i = -1;
	ret = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * (num + 1));
	while (++i < num)
		ret[i] = malloc(sizeof(pthread_mutex_t));
	ret[i] = 0;
	i = -1;
	while (++i < num)
		pthread_mutex_init(ret[i], NULL);
	return (ret);
}

void				*sobaka(void *ar)
{
	int		right_hand;
	int		left_hand;

	left_hand = *(int*)ar;
	right_hand = *(int*)ar + 1;
	if (!forks[right_hand])
		right_hand = 0;
	pthread_mutex_lock(forks[right_hand]);
	pthread_mutex_lock(forks[left_hand]);
	grabbing_forks(left_hand);
	eating(left_hand);
	sleeping(left_hand);
	thinking(left_hand);
	write(1, "\n", 1);
	pthread_mutex_unlock(forks[right_hand]);
	pthread_mutex_unlock(forks[left_hand]);
	return (NULL);
}

static int			philo_config(int ac, char **av, t_phi_data *philos)
{
	int i;
	int j;

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
	philos->num = not_atoi(av[1]);
	if (philos->num < 2)
		return (puterr());
	philos->time_to_die = not_atoi(av[2]);
	philos->time_to_eat = not_atoi(av[3]);
	philos->time_to_sleep = not_atoi(av[4]);
	philos->num_eat = (ac == 6) ? not_atoi(av[5]) : -1;
	return (0);
}

int					main(int ac, char **av)
{
	t_phi_data		philos;
	int				i;
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (ac < 5 || ac > 6)
		return (puterr());
	if (philo_config(ac, av, &philos))
		return (1);
	i = -1;
	forks = create_mutex(philos.num);
	philos.phil = malloc(sizeof(pthread_t) * philos.num);
	philos.p = malloc(sizeof(int) * philos.num);
	while (++i < philos.num)
		philos.p[i] = i;
	i = -1;
	while (++i < philos.num)
		pthread_create(&philos.phil[i], NULL, sobaka, (void*)&philos.p[i]);
	getchar();
	printf("\n%zd\n%d\n", time.tv_sec, time.tv_usec);
	i = -1;
	while (++i < philos.num)
		pthread_mutex_destroy(forks[i]);
	i = -1;
	while (++i < philos.num)
		pthread_detach(philos.phil[i]);
	free(forks);
	free(philos.phil);
	free(philos.p);
	return (0);
}

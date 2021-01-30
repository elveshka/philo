/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:02:04 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 10:48:30 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_sim_start(t_info *info)
{
	pthread_t		sim;
	int				i;

	info->sim_start = ft_time();
	i = 0;
	while (i < info->number_philo)
	{
		if (pthread_create(&sim, 0, &ft_sim_phi, (void*)&info->philo[i]))
		{
			ft_error(ERROR_FOR);
			return (0);
		}
		info->philo[i].last_meal = ft_time();
		if (pthread_detach(sim))
		{
			ft_error(ERROR_FIFE);
			return (0);
		}
		usleep(100);
		i++;
	}
	while (!ft_stop_sim(info))
		usleep(100);
	return (1);
}

void	ft_parser(char **argv, t_info *info)
{
	info->number_philo = ft_atoi(argv[1]);
	info->time_live = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->number_eat = ft_atoi(argv[5]);
}

int		main(int argc, char **argv)
{
	t_info		info;

	if (argc < 5 || argc > 6)
		return (ft_error(ERROR_ONE));
	if (!ft_isnumber(argv[1]))
		return (ft_error(ERROR_ONE));
	if (!ft_isnumber(argv[2]))
		return (ft_error(ERROR_ONE));
	if (!ft_isnumber(argv[3]))
		return (ft_error(ERROR_ONE));
	if (!ft_isnumber(argv[4]))
		return (ft_error(ERROR_ONE));
	if (argv[5])
		if (!ft_isnumber(argv[5]))
			return (ft_error(ERROR_ONE));
	info = ft_init_info();
	ft_parser(argv, &info);
	if (!ft_init(&info))
		return (1);
	if (!ft_sim_start(&info))
		return (1);
	return (0);
}

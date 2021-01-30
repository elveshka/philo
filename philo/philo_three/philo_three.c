/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:31:49 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 17:39:54 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_kill_pr(t_info *info)
{
	int i;

	i = 0;
	while (i < info->number_philo)
	{
		kill(info->process[i], SIGKILL);
		i++;
	}
}

int		ft_sim_start(t_info *info)
{
	int	i;

	info->sim_start = ft_time();
	i = 0;
	while (i < info->number_philo)
	{
		info->philo[i].last_meal = ft_time();
		info->process[i] = fork();
		if (info->process[i] < 0)
		{
			ft_error(ERROR_FOR);
			ft_kill_pr(info);
			return (0);
		}
		else if (info->process[i] == 0)
			ft_sim_phi(&info->philo[i]);
		usleep(100);
		i++;
	}
	ft_sim_control(info);
	sem_wait(info->end_sim);
	ft_kill_pr(info);
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
	sleep(5);
	return (0);
}

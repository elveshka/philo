/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:27:20 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 10:22:56 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_info	ft_init_info(void)
{
	t_info		info;

	info.time_eat = 0;
	info.time_sleep = 0;
	info.time_live = 0;
	info.number_philo = 0;
	info.number_eat = 0;
	info.finish = 0;
	return (info);
}

int		ft_mutex_init(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->number_philo)
	{
		if (pthread_mutex_init(&info->fork[i], 0) != 0)
		{
			ft_error(ERROR_THREE);
			return (0);
		}
		if (pthread_mutex_init(&info->philo[i].eating_now, 0) != 0)
		{
			ft_error(ERROR_THREE);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&info->pencil, 0) != 0)
	{
		ft_error(ERROR_THREE);
		return (0);
	}
	return (1);
}

int		ft_allocate_memory(t_info *info)
{
	info->philo = (t_description*)malloc(sizeof(t_description)
				* info->number_philo);
	if (!info->philo)
	{
		ft_error(ERROR_TWO);
		return (0);
	}
	info->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
				* info->number_philo);
	if (!info->fork)
	{
		ft_error(ERROR_TWO);
		return (0);
	}
	return (1);
}

int		ft_init(t_info *info)
{
	int		i;

	if (!ft_allocate_memory(info))
		return (0);
	if (!ft_mutex_init(info))
		return (0);
	i = 0;
	while (i < info->number_philo)
	{
		info->philo[i].left_fork = i;
		info->philo[i].right_fork = (i + 1) % info->number_philo;
		info->philo[i].location = i + 1;
		info->philo[i].meals = 0;
		info->philo[i].info = info;
		i++;
	}
	return (1);
}

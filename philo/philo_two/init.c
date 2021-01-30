/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:09:39 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 10:46:47 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int		ft_init_obj_sem(t_info *info)
{
	sem_unlink("/fork");
	sem_unlink("/pencil");
	info->pencil = sem_open("/pencil", O_CREAT | O_EXCL, 0666, 1);
	if (info->pencil == SEM_FAILED)
	{
		ft_error(ERROR_THREE);
		return (0);
	}
	info->fork = sem_open("/fork", O_CREAT | O_EXCL, 0666, info->number_philo);
	if (info->fork == SEM_FAILED)
	{
		ft_error(ERROR_THREE);
		return (0);
	}
	return (1);
}

int		ft_init_status_sem(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->number_philo)
	{
		sem_unlink("/eating_now");
		info->philo[i].eating_now =
					sem_open("/eating_now", O_CREAT | O_EXCL, 0666, 1);
		if (info->philo[i].eating_now == SEM_FAILED)
		{
			ft_error(ERROR_THREE);
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_allocate_memory(t_info *info)
{
	info->philo =
			(t_description*)malloc(sizeof(t_description) * info->number_philo);
	if (!info->philo)
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
	if (!ft_init_obj_sem(info))
		return (0);
	if (!ft_init_status_sem(info))
		return (0);
	i = 0;
	while (i < info->number_philo)
	{
		info->philo[i].location = i + 1;
		info->philo[i].meals = 0;
		info->philo[i].info = info;
		i++;
	}
	return (1);
}

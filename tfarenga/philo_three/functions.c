/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:40:06 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/06 16:45:49 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_take_forks(t_description *phi)
{
	if (sem_wait(phi->info->fork) < 0)
		return ;
	ft_text(phi, "fork");
	if (sem_wait(phi->info->fork) < 0)
		return ;
	ft_text(phi, "fork");
}

void	ft_eating(t_description *phi)
{
	if (sem_wait(phi->eating_now) < 0)
		return ;
	ft_text(phi, "eat");
	phi->last_meal = ft_time();
	phi->meals++;
	if (sem_post(phi->eating_now) < 0)
		return ;
	usleep(1000 * phi->info->time_eat);
	if (sem_post(phi->info->fork) < 0)
		return ;
	if (sem_post(phi->info->fork) < 0)
		return ;
}

void	ft_sleep_and_think(t_description *phi)
{
	ft_text(phi, "sleep");
	usleep(1000 * phi->info->time_sleep);
	ft_text(phi, "think");
}

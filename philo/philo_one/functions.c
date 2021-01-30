/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:47:34 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/03 18:22:07 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_take_forks(t_description *phi)
{
	if (pthread_mutex_lock(&phi->info->fork[phi->left_fork]))
		return ;
	ft_text(phi, "fork");
	if (pthread_mutex_lock(&phi->info->fork[phi->right_fork]))
		return ;
	ft_text(phi, "fork");
}

void	ft_eating(t_description *phi)
{
	if (pthread_mutex_lock(&phi->eating_now))
		return ;
	ft_text(phi, "eat");
	phi->last_meal = ft_time();
	phi->meals++;
	if (pthread_mutex_unlock(&phi->eating_now))
		return ;
	usleep(1000 * phi->info->time_eat);
	if (pthread_mutex_unlock(&phi->info->fork[phi->left_fork]))
		return ;
	if (pthread_mutex_unlock(&phi->info->fork[phi->right_fork]))
		return ;
}

void	ft_sleep_and_think(t_description *phi)
{
	ft_text(phi, "sleep");
	usleep(1000 * phi->info->time_sleep);
	ft_text(phi, "think");
}

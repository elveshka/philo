/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:31:44 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 11:01:25 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*ft_check_phi(void *arg)
{
	t_description	*phi;

	phi = (t_description*)arg;
	while (1)
	{
		if (sem_wait(phi->eating_now) < 0)
			return ((void*)0);
		if (((ft_time() - phi->last_meal) > phi->info->time_live))
		{
			ft_text(phi, "death");
			sem_post(phi->info->end_sim);
			return ((void*)0);
		}
		if (sem_post(phi->eating_now) < 0)
			return ((void*)0);
		if (phi->info->number_eat > 0)
			if (phi->meals >= phi->info->number_eat)
				sem_post(phi->eating_finish);
		usleep(500);
	}
	return ((void*)0);
}

void	*ft_sim_phi(t_description *phi)
{
	pthread_t		sim;

	if (pthread_create(&sim, 0, &ft_check_phi, (void*)phi))
	{
		ft_error(ERROR_FOR);
		exit(1);
	}
	if (pthread_detach(sim))
	{
		ft_error(ERROR_FIFE);
		exit(1);
	}
	while (1)
	{
		ft_take_forks(phi);
		ft_eating(phi);
		ft_sleep_and_think(phi);
	}
}

void	*ft_eating_control(void *arg)
{
	t_info		*info;
	int			i;

	info = (t_info*)arg;
	i = 0;
	while (i < info->number_philo)
	{
		sem_wait(info->philo[i].eating_finish);
		i++;
	}
	sem_post(info->end_sim);
	return ((void*)0);
}

void	ft_sim_control(t_info *info)
{
	pthread_t	sim;

	if (pthread_create(&sim, 0, &ft_eating_control, (void*)info))
	{
		ft_error(ERROR_FOR);
		ft_kill_pr(info);
		exit(1);
	}
	if (pthread_detach(sim))
	{
		ft_error(ERROR_FIFE);
		ft_kill_pr(info);
		exit(1);
	}
}

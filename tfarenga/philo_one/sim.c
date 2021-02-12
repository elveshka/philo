/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:25:44 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 10:21:21 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_text_two(char *type_txt)
{
	if (!ft_strcmp(type_txt, "fork"))
		ft_putstr(" has taken a fork\n");
	else if (!ft_strcmp(type_txt, "think"))
		ft_putstr(" is thinking\n");
	else if (!ft_strcmp(type_txt, "eat"))
		ft_putstr(" is eating\n");
	else if (!ft_strcmp(type_txt, "sleep"))
		ft_putstr(" is sleeping\n");
}

void	ft_text(t_description *phi, char *type_txt)
{
	if (pthread_mutex_lock(&phi->info->pencil) != 0)
		return ;
	ft_putnbr(ft_time() - phi->info->sim_start);
	ft_putchar('\t');
	ft_putnbr(phi->location);
	if (!ft_strcmp(type_txt, "death"))
	{
		ft_putstr(" died\n");
		return ;
	}
	ft_text_two(type_txt);
	if (pthread_mutex_unlock(&phi->info->pencil) != 0)
		return ;
}

void	*ft_check_phi(void *arg)
{
	t_description	*phi;

	phi = (t_description*)arg;
	while (!phi->info->finish)
	{
		if (pthread_mutex_lock(&phi->eating_now))
			return ((void*)0);
		if (((ft_time() - phi->last_meal) > phi->info->time_live))
		{
			ft_text(phi, "death");
			phi->info->finish = 1;
			return ((void*)0);
		}
		if (pthread_mutex_unlock(&phi->eating_now))
			return ((void*)0);
		usleep(500);
	}
	return ((void*)0);
}

void	*ft_sim_phi(void *arg)
{
	t_description	*phi;
	pthread_t		sim;

	phi = (t_description*)arg;
	if (pthread_create(&sim, 0, &ft_check_phi, (void*)phi))
	{
		ft_error(ERROR_FOR);
		return ((void*)0);
	}
	if (pthread_detach(sim))
	{
		ft_error(ERROR_FIFE);
		return ((void*)0);
	}
	while (!phi->info->finish)
	{
		ft_take_forks(phi);
		ft_eating(phi);
		ft_sleep_and_think(phi);
	}
	return ((void*)0);
}

int		ft_stop_sim(t_info *info)
{
	int		i;
	int		number;

	number = 0;
	i = 0;
	if (info->finish == 1)
		return (1);
	if (info->number_eat > 0)
	{
		while (i < info->number_philo)
		{
			if (info->philo[i].meals >= info->number_eat)
			{
				number++;
				if (number == info->number_philo)
				{
					info->finish = 1;
					return (1);
				}
			}
			i++;
		}
	}
	return (0);
}

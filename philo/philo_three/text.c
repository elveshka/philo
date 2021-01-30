/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:32:22 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/06 17:32:50 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	if (sem_wait(phi->info->pencil) < 0)
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
	if (sem_post(phi->info->pencil) < 0)
		return ;
}

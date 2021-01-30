/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:24:37 by esnowbal          #+#    #+#             */
/*   Updated: 2021/01/30 16:50:51 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

typedef struct		s_phi_data
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
}					t_phi_data;

int					not_atoi(const char *str);
int					not_isdigit(int c);
int					puterr(void);

#endif

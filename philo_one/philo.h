/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:24:37 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/03 14:11:45 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct		s_data
{
	int				num;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				num_eat;
	pthread_t		*threads;
}					t_data;

typedef struct		s_phil
{
	int				index;
	unsigned long	living_time;
	unsigned long	start_time;
	int				died;
	int				meal_times;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_data			*data;
}					t_phil;

int					not_atoi(const char *str);
int					not_isdigit(int c);
int					puterr(void);
int					not_strlen(char *s);
void				eating(t_phil *phil);
void				sleeping(t_phil *phil);
void				thinking(t_phil *phil);
void				grabbing_forks(t_phil *phil);
unsigned long		get_time(void);
t_phil				*philos_init(t_data *data, pthread_mutex_t **forks);
int					philo_config(int ac, char **av, t_data *data);
pthread_mutex_t		**create_mutex(int num);

#endif

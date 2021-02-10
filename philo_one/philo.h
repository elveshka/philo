/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:24:37 by esnowbal          #+#    #+#             */
/*   Updated: 2021/02/10 15:15:58 by esnowbal         ###   ########.fr       */
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
	long			start_time;
	pthread_t		*threads;
}					t_data;

typedef struct		s_phil
{
	int				index;
	long			living_time;
	long			start_meal;
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
int					eating(t_phil *phil);
int					sleeping(t_phil *phil);
int					thinking(t_phil *phil);
void				grabbing_forks(t_phil *phil);
long				get_time(void);
t_phil				*philos_init(t_data *data, pthread_mutex_t **forks);
int					philo_config(int ac, char **av, t_data *data);
pthread_mutex_t		**create_mutex(int num);

#endif

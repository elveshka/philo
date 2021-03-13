/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowbal <esnowbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:24:37 by esnowbal          #+#    #+#             */
/*   Updated: 2021/03/13 16:47:50 by esnowbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>

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
	long			start_meal;
	int				meal_times;
	t_data			*data;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*waiter;
}					t_phil;

int					not_atoi(const char *str);
int					not_isdigit(int c);
int					puterr(void);
int					not_strlen(char *s);
int					eating(t_phil *phil);
void				sleeping(t_phil *phil);
void				thinking(t_phil *phil);
void				grabbing_forks(t_phil *phil);
long				get_time(void);
t_phil				*philos_init(t_data *data, sem_t **forks, sem_t *print);
int					philo_config(int ac, char **av, t_data *data);
void				waste_of_time(int time_to_waste);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:08:02 by tfarenga          #+#    #+#             */
/*   Updated: 2020/11/09 11:43:58 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>

# define ERROR_ONE "Invalid argument"
# define ERROR_TWO "No memory allocated"
# define ERROR_THREE "Failed to initialize semaphore object"
# define ERROR_FOR "No flow"
# define ERROR_FIFE "The flow is not broken"

typedef struct		s_description
{
	struct s_info	*info;
	sem_t			*eating_now;
	int				location;
	int				meals;
	int				last_meal;

}					t_description;

typedef struct		s_info
{
	int				time_sleep;
	int				time_eat;
	int				time_live;
	int				number_philo;
	int				number_eat;
	int				finish;
	t_description	*philo;
	sem_t			*fork;
	sem_t			*pencil;
	int				sim_start;
}					t_info;

int					ft_error(char *str);
int					ft_isnumber(char *str);
int					ft_isdigit(char str);
int					ft_atoi(char *str);
int					ft_strlen(char *str);

int					ft_time(void);
void				ft_putchar(char c);
void				ft_putnbr(int n);
int					ft_strcmp(char *s1, char *s2);
void				ft_putstr(char *str);

t_info				ft_init_info(void);
int					ft_allocate_memory(t_info *info);
int					ft_init_obj_sem(t_info *info);
int					ft_init_status_sem(t_info *info);
int					ft_init(t_info *info);

void				*ft_sim_phi(void *arg);
int					ft_stop_sim(t_info *info);
void				*ft_check_phi(void *arg);

void				ft_text(t_description *phi, char *type_txt);
void				ft_text_two(char *type_txt);
void				ft_take_forks(t_description *phi);
void				ft_eating(t_description *phi);
void				ft_sleep_and_think(t_description *phi);

#endif

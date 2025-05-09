/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:01:49 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/09 20:44:03 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
# define PHILO_MAX 300

typedef struct s_info
{
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			philo_ready;
	bool			end_simulation;
	int				philo_nbr;
	pthread_t	stop_thread;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	death;
	pthread_mutex_t	stop;
}		t_info;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	t_info			*infos;
}		t_philo;


int	ft_atoi(const char *str);
long	ft_atol(const char *str);
void	init_program(t_info *infos);
int		init_infos(t_info *infos, char **params);
void	init_forks(pthread_mutex_t *forks, int philo_nbr);
int	creating_philosopher(t_philo *philos, char **params, pthread_mutex_t *forks, t_info *infos);
void	create_threads(t_info *infos, t_philo *philos);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
long	get_time();
void	precise_usleep(long usec, t_info *infos);
void	print(char	*msg, t_philo *philo);

void	*manager(void *arg);
#endif
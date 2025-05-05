/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:01:49 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/05 23:17:44 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
# include <time.h>
# define PHILO_MAX 300

typedef struct s_info
{
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	int				philo_nbr;
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
void	init_infos(t_info *infos, char **params);
void	init_forks(pthread_mutex_t *forks, int philo_nbr);
void	creating_philosopher(t_philo *philos, char **params, pthread_mutex_t *forks, t_info *infos);
void	create_threads(t_info *infos, t_philo *philos);
#endif
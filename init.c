/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:47:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 08:52:34 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int philo_nbr)
{
	long	i;

	i = 0;
	while (i < philo_nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_control_threads(t_info *infos)
{
	pthread_mutex_init(&infos->print, NULL);
	pthread_mutex_init(&infos->meal, NULL);
	pthread_mutex_init(&infos->death, NULL);
	pthread_mutex_init(&infos->stop, NULL);
}

int	init_infos(t_info *infos, char **params)
{
	infos->philo_nbr = ft_atol(params[1]);
	infos->time_to_die = ft_atol(params[2]);
	infos->time_to_eat = ft_atol(params[3]);
	infos->time_to_sleep = ft_atol(params[4]);
	if (params[5])
		infos->nbr_limit_meals = ft_atol(params[5]);
	else
		infos->nbr_limit_meals = -1;
	if (infos->philo_nbr <= 0 || infos->time_to_die <= 0
		|| infos->time_to_eat <= 0 || infos->time_to_sleep <= 0)
		return (1);
	infos->end_simulation = false;
	return (0);
}

void	init_philo(t_philo *philo, int i, pthread_mutex_t *forks, t_info *infos)
{
	philo->id = i + 1;
	philo->meals_counter = 0;
	philo->last_meal_time = 0;
	philo->left_fork = &forks[i];
	if (i == 0)
		philo->right_fork = &forks[infos->philo_nbr - 1];
	else
		philo->right_fork = &forks[i - 1];
	philo->infos = infos;
}

int	creating_philosopher(t_philo *philos, char **params,
	pthread_mutex_t *forks, t_info *infos)
{
	int	i;
	int	nbr_philo;

	i = 0;
	nbr_philo = ft_atoi(params[1]);
	if (init_infos(infos, params) == 1)
		return (1);
	while (i < nbr_philo)
	{
		init_philo(&philos[i], i, forks, infos);
		i++;
	}
	return (0);
}

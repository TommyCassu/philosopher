/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:47:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/03 02:41:51 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
long	ft_atol(const char *str)
{
	int	i;
	long	sign;
	long	result;
	int	t;

	i = 0;
	t = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		t++;
		i++;
	}
	if (t > 1)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return (result * sign);
}

void	parsing_params(t_philo *philo, char **params)
{
	philo->philo_nbr = ft_atol(params[1]);
	philo->time_to_die = ft_atol(params[2]);
	philo->time_to_eat= ft_atol(params[3]);
	philo->time_to_sleep = ft_atol(params[4]);
	if (params[5])
		philo->nbr_limit_meals = ft_atol(params[5]);
	else
		philo->nbr_limit_meals = -1;
	if (philo->philo_nbr <= 0 || philo->time_to_die <= 0 || philo->time_to_eat <= 0
		|| philo->time_to_sleep <= 0)
		return ;
	philo->end_simulation = false;
}

void	init_philo(t_philo *philo, int i, pthread_mutex_t *forks, int nbr_philo)
{
	philo->id = i;
	philo->meals_counter = 0;
	philo->full = false;
	philo->last_meal_time = 0;
	philo->left_fork = &forks[i];
	if (i == 0)
		philo->right_fork = &forks[nbr_philo - 1];
	else
		philo->right_fork = &forks[i - 1];
}

void	creating_philosopher(t_philo *philos, char **params, pthread_mutex_t *forks)
{
	int	i;
	int	nbr_philo;
	
	i = 0;
	nbr_philo = ft_atoi(params[1]);
	philos = malloc(sizeof(t_philo) * nbr_philo);
	if (!philos)
		return ;
	while (i < nbr_philo)
	{
		parsing_params(&philos[i], params);
		init_philo(&philos[i], i, forks, nbr_philo);
		i++;
	}
}

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
/*
void	init_data(t_table *table)
{
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return ;
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->philos)
		return ;
}*/

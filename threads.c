/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:43:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 20:22:22 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_one(t_philo *philo)
{
	print("is thinking", philo);
	pthread_mutex_lock(philo->left_fork);
	print("has taken a fork", philo);
	precise_usleep(philo->infos->time_to_die, philo->infos);
	print("died", philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->infos->stop);
	philo->infos->end_simulation = true;
	pthread_mutex_unlock(&philo->infos->stop);
	return ;
}

void	routine(t_philo *philo)
{
	print("is thinking", philo);
	take_forks(philo);
	eat(philo);
	ft_sleep(philo);
	usleep(10);
}

void	*philo_process(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->infos->philo_nbr == 1)
	{
		philo_one(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(philo->infos->time_to_eat / 2, philo->infos);
	while (1)
	{
		pthread_mutex_lock(&philo->infos->stop);
		if (philo->infos->end_simulation == true)
		{
			pthread_mutex_unlock(&philo->infos->stop);
			break ;
		}
		pthread_mutex_unlock(&philo->infos->stop);
		routine(philo);
		i++;
	}
	return (NULL);
}

void	create_threads(t_info *infos, t_philo *philos)
{
	int	i;

	i = 0;
	infos->start_simulation = get_time();
	while (i < infos->philo_nbr)
	{
		philos[i].last_meal_time = infos->start_simulation;
		pthread_create(&(philos[i].thread_id), NULL, philo_process, &philos[i]);
		i++;
	}
	if (pthread_create(&(infos->stop_thread), NULL, manager, philos) != 0)
		perror("pthread_create death_thread");
	i = 0;
	pthread_join(infos->stop_thread, NULL);
	while (i < infos->philo_nbr)
	{
		pthread_join((philos[i].thread_id), NULL);
		i++;
	}
	return ;
}

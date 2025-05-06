/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:58:53 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/06 19:48:22 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("[%ld ms] Philosopher %d has taken left fork\n", get_time() - philo->infos->start_simulation, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("[%ld ms] Philosopher %d has taken right fork\n", get_time() - philo->infos->start_simulation, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("[%ld ms] Philosopher %d has taken right fork\n", get_time() - philo->infos->start_simulation, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("[%ld ms] Philosopher %d has taken left fork\n", get_time() - philo->infos->start_simulation, philo->id);
	}
	printf("[%ld ms] Philosopher %d Eat\n", get_time() - philo->infos->start_simulation , philo->id);
	philo->last_meal_time = get_time();
	philo->meals_counter++;
	precise_usleep(philo->infos->time_to_eat, philo->infos);
	pthread_mutex_unlock(philo->left_fork);
	printf("[%ld ms] Philosopher %d has realise left fork\n", get_time() - philo->infos->start_simulation, philo->id);
	pthread_mutex_unlock(philo->right_fork);
	printf("[%ld ms] Philosopher %d has release right fork\n", get_time() - philo->infos->start_simulation , philo->id);
}

void	ft_sleep(t_philo *philo)
{
	printf("[%ld ms] Philosopher %d sleeping\n", get_time() - philo->infos->start_simulation, philo->id);
	precise_usleep(philo->infos->time_to_sleep, philo->infos);
}

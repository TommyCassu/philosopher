/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:58:53 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/11 22:56:04 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->death);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->infos->death);
	print("is eating", philo);
	precise_usleep(philo->infos->time_to_eat, philo->infos);
	pthread_mutex_lock(&philo->infos->meal);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->infos->meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	print("is sleeping", philo);
	precise_usleep(philo->infos->time_to_sleep, philo->infos);
}

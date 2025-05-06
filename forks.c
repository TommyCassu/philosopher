/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:58:53 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/07 00:47:34 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print("Has taken left fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print("Has taken right fork", philo);	
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print("Has taken right fork", philo);

		pthread_mutex_lock(philo->left_fork);
		print("Has taken left fork", philo);
	}
	pthread_mutex_lock(&philo->infos->meal);
	philo->last_meal_time = get_time();
	philo->meals_counter++;
	print("Eat", philo);
	pthread_mutex_unlock(&philo->infos->meal);
	precise_usleep(philo->infos->time_to_eat, philo->infos);
	pthread_mutex_unlock(philo->left_fork);
	print("Has release left fork", philo);
	pthread_mutex_unlock(philo->right_fork);
	print("Has release right fork", philo);
}

void	ft_sleep(t_philo *philo)
{
	print("Sleeping", philo);
	precise_usleep(philo->infos->time_to_sleep, philo->infos);
}

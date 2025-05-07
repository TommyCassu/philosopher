/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:58:53 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/07 11:15:59 by tcassu           ###   ########.fr       */
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
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->dead);
	philo->last_meal_time = get_time();
	print("Eat", philo);
	pthread_mutex_unlock(&philo->infos->dead);
	precise_usleep(philo->infos->time_to_eat, philo->infos);
	pthread_mutex_lock(&philo->infos->meal);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->infos->meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
void	ft_sleep(t_philo *philo)
{
	print("Sleeping", philo);
	precise_usleep(philo->infos->time_to_sleep, philo->infos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:42:47 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 18:45:11 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	verif_death(t_philo *philo, t_info *info)
{
	long	last_meal;

	pthread_mutex_lock(&info->death);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&info->death);
	if ((get_time() - last_meal) > info->time_to_die)
	{
		print("died", philo);
		pthread_mutex_lock(&info->stop);
		info->end_simulation = true;
		pthread_mutex_unlock(&info->stop);
	}
}

int	verif_stop(t_philo *philo, t_info *info)
{
	int	i;
	int	status_meal_max;

	i = 0;
	status_meal_max = 1;
	if (info->nbr_limit_meals == -1)
		status_meal_max = 0;
	while (i < info->philo_nbr)
	{
		verif_death(&philo[i], info);
		if (status_meal_max == 1)
		{
			pthread_mutex_lock(&info->meal);
			if (philo[i].meals_counter < info->nbr_limit_meals)
				status_meal_max = 0;
			pthread_mutex_unlock(&info->meal);
		}
		pthread_mutex_lock(&info->stop);
		if (info->end_simulation == true)
		{
			pthread_mutex_unlock(&info->stop);
			break ;
		}
		pthread_mutex_unlock(&info->stop);
		i++;
	}
	return (status_meal_max);
}

void	*manager(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos->infos->stop);
		if (philos->infos->end_simulation == true)
		{
			pthread_mutex_unlock(&philos->infos->stop);
			break ;
		}
		pthread_mutex_unlock(&philos->infos->stop);
		if (verif_stop(philos, philos->infos))
		{
			print("Tous le monde a fini de manger", philos);
			pthread_mutex_lock(&philos->infos->stop);
			philos->infos->end_simulation = true;
			pthread_mutex_unlock(&philos->infos->stop);
			break ;
		}
		precise_usleep(5, philos->infos);
	}
	return (NULL);
}

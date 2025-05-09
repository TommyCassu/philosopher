/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:42:47 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/09 19:15:44 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    verif_death(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->death);
    if ((get_time() - philo->last_meal_time) >= info->time_to_die)
    {
        pthread_mutex_lock(&info->stop);
        print("died", philo);
        info->end_simulation = true;
        pthread_mutex_unlock(&info->stop);
    }
    pthread_mutex_unlock(&info->death);
}

int	verif_stop(t_philo *philo, t_info *info)
{
	int i;
    int status_meal_max;
    
    i = 0;
    status_meal_max = 1;
    while (i < info->philo_nbr)
    {
        verif_death(&philo[i], info);
        pthread_mutex_lock(&info->meal);
        if (philo[i].meals_counter < info->nbr_limit_meals)
            status_meal_max = 0;
        if (info->nbr_limit_meals == -1)
            status_meal_max = 0;
        pthread_mutex_unlock(&info->meal);
        if (info->end_simulation == true)
            break ;
        i++;
    }
    
    return (status_meal_max);
}

void	*manager(void *arg)
{
	t_philo	*philos;
	
	philos = (t_philo *)arg;
	while (philos->infos->end_simulation == false)
	{
		if (verif_stop(philos, philos->infos))
        {
            pthread_mutex_lock(&philos->infos->stop);
            print("Tous le monde a fini de manger", philos);
            philos->infos->end_simulation = true;
            pthread_mutex_unlock(&philos->infos->stop);
        }    
		precise_usleep(5, philos->infos);
	}
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:43:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/07 17:37:58 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_process(void *arg)
{
	t_philo	*philo;
	int i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(1, philo->infos);
	while (philo->infos->end_simulation == false)
	{
		if (philo->infos->end_simulation == true)
			break;
		print("is thinking", philo);
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
		i++;
	}
	return NULL;
}
int	verif_nb_meals(t_info *info)
{
	
}

void	*verif_death(void *arg)
{
	t_philo	*philos;
	
	philos = (t_philo *)arg;
	while (philos->infos->end_simulation == false)
	{
		if (verif_nb_meals(philos->infos))
		{
			check_meals(philos->infos);
		}
		precise_usleep(100, philos->infos);
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
	if (pthread_create(&(infos->death_thread), NULL, verif_death, philos) != 0)
    	perror("pthread_create death_thread");
	i = 0;
	while (i < infos->philo_nbr)
	{
		pthread_join((philos[i].thread_id), NULL);
		i++;
	}
	pthread_join(infos->death_thread, NULL);
	return ;
}





/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:43:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/06 19:53:29 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
			write(1, "Eating\n", 7);
			sleep(); // time to eat
			philo->meals_counter++;
			set new last meal value
			release fork
			start to sleep			
			*/
void	*philo_process(void *arg)
{
	t_philo	*philo;
	int i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		precise_usleep(philo->infos->time_to_eat, philo->infos);
	while (i < 5)
	{
		take_forks(philo);
		ft_sleep(philo);
		i++;
	}
	return NULL;
}

void	*verif_death(void *arg)
{
	t_philo	*philos;
	int		i;
	long	now;
	
	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos->infos->philo_nbr)
		{
			now = get_time();
			if (now - philos[i].last_meal_time >= philos->infos->time_to_die)
			{
				philos->infos->end_simulation = true;
				printf("[%ld ms] Philosopher %d is dead\n", get_time() - philos->infos->start_simulation, philos[i].id);
				return NULL;
			}
			i++;
		}
		precise_usleep(100, philos->infos);
	}
	return NULL;
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
	
	return ;
}





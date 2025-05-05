/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:43:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/05 23:46:45 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1);
	while (!is_dead(philo))
	{
		if (philo->meals_counter == 0 && philo.infos->nbr_limit_meals == 0)
			return ;
		take_left_fork();
		if (l_fork)
			take_right_fork();
		if (l_fork && r_fork)
		{
			/*
			write(1, "Eating\n", 7);
			sleep(); // time to eat
			philo->meals_counter++;
			set new last meal value
			release fork
			start to sleep			
			*/
		}
	}
	return NULL;
}

void	create_threads(t_info *infos, t_philo *philos)
{
	int	i;
	
	i = 0;
	infos->start_simulation = time(NULL);
	while (i < infos->philo_nbr)
	{
		pthread_create(&(philos[i].thread_id), NULL, philo_process, &philos[i]);
		i++;
	}
	i = 0;
	while (i < infos->philo_nbr)
	{
		pthread_join((philos[i].thread_id), NULL);
		i++;
	}
	return ;
}





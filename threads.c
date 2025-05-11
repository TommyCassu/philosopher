/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:43:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/11 22:58:34 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_one(t_philo *philo)
{
	print("is thinking", philo);
	pthread_mutex_lock(philo->right_fork);
	print("has taken a fork", philo);
	precise_usleep(philo->infos->time_to_die, philo->infos);
	print("died", philo);
	pthread_mutex_unlock(philo->right_fork);
	philo->infos->end_simulation = true;
	return ;
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
	while (philo->infos->end_simulation == false)
	{
		if (philo->infos->end_simulation == true)
			break ;
		print("is thinking", philo);
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
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

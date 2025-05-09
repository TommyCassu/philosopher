/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:11:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/09 20:00:08 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]

int main(int ac, char *av[])
{
	t_info	infos;
	t_philo philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];
	
	if (ac == 5 || ac == 6)
	{
		//check errors
		//Init data
		init_forks(forks, ft_atoi(av[1]));
		if (creating_philosopher(philos, av, forks, &infos) == 1)
			return (0);
		init_program(&infos);
		create_threads(&infos, philos);
		// dyning
		
		//clean program
		
	}
	
}
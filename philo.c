/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:11:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/09 23:25:26 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]
int	verif_params(char **params)
{
	if (ft_atol(params[1]) <= 0)
	{
		printf("Error : Enter a valid number of philosopher");
		return (1);
	}
	else if (ft_atol(params[2]) < 60 || ft_atol(params[3]) < 60
		|| ft_atol(params[4]) < 60)
	{
		printf("Error : Enter a valid time (more than 60ms)");
		return (1);
	}
	else if ((params[5]))
	{
		if (ft_atol(params[5]) <= 0)
		{
			printf("Error : Enter a valid number of meals");
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_info			infos;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac == 5 || ac == 6)
	{
		//check errors
		if (verif_params(av) == 1)
			return (0);
		//Init data
		init_forks(forks, ft_atoi(av[1]));
		if (creating_philosopher(philos, av, forks, &infos) == 1)
			return (0);
		init_program(&infos);
		create_threads(&infos, philos);
		//clean program
	}
	else
	{
		printf("Error usage : ./philo nbr_philosophers time_to_die");
		printf(" time_to_eattime_to_sleep [nbr_of_meals]");
	}
	return (0);
}

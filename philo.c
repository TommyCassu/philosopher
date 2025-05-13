/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:11:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 19:38:57 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:11:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/11 20:17:54 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close(t_philo *philos, t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	(void)philos;
	while (i < info->philo_nbr)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->meal);
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->stop);
}

int	verif_params(char **params)
{
	if (ft_atol(params[1]) <= 0 || ft_atol(params[1]) > 200)
	{
		printf("Error : Enter a valid number of philosopher [1 - 200]");
		return (1);
	}
	else if (ft_atol(params[2]) < 60 || ft_atol(params[3]) < 60
		|| ft_atol(params[4]) < 60)
	{
		printf("Error : Enter a valid time ");
		printf("(between 60ms and 9223372036854775807ms)\n");
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
		if (verif_params(av) == 1)
			return (0);
		init_forks(forks, ft_atoi(av[1]));
		if (creating_philosopher(philos, av, forks, &infos) == 1)
			return (0);
		init_control_threads(&infos);
		create_threads(&infos, philos);
		ft_close(philos, &infos, forks);
	}
	else
	{
		printf("Error usage : ./philo nbr_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep [nbr_of_meals]");
	}
	return (0);
}

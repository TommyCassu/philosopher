/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:11:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/05 20:47:13 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;
	int	t;

	i = 0;
	t = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		t++;
		i++;
	}
	if (t > 1)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return (result * sign);
}

int main(int ac, char *av[])
{
	t_philo philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];
	
	if (ac == 5 || ac == 6)
	{
		//check errors
		//Init data
		init_forks(forks, ft_atoi(av[1]));
		creating_philosopher(philos, av, forks);

		// dyning
		
		//clean program
		
	}
	
}
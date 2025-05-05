/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:31:37 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/03 02:25:08 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int	i;
	long	sign;
	long	result;
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

void	parsing_params(t_philo *philo, char **params)
{
	philo->philo_nbr = ft_atol(params[1]);
	philo->time_to_die = ft_atol(params[2]);
	philo->time_to_eat= ft_atol(params[3]);
	philo->time_to_sleep = ft_atol(params[4]);
	if (params[5])
		philo->nbr_limit_meals = ft_atol(params[5]);
	else
		philo->nbr_limit_meals = -1;
	if (philo->philo_nbr <= 0 || philo->time_to_die <= 0 || philo->time_to_eat <= 0
		|| philo->time_to_sleep <= 0)
		return ;
	philo->end_simulation = false;
}
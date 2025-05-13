/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:00:47 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 18:12:23 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char	*msg, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->infos->print);
	pthread_mutex_lock(&philo->infos->stop);
	if (philo->infos->end_simulation == false)
	{
		current_time = get_time() - philo->infos->start_simulation;
		printf("%ld %d %s\n", current_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->infos->stop);
	pthread_mutex_unlock(&philo->infos->print);
}

void	precise_usleep(long ms, t_info *infos)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time();
	while (get_time() - start < ms)
	{
		pthread_mutex_lock(&infos->stop);
		if (infos->end_simulation == true)
		{
			pthread_mutex_unlock(&infos->stop);
			return ;
		}
		pthread_mutex_unlock(&infos->stop);
		elapsed = get_time() - start;
		rem = ms - elapsed;
		if (rem > 1)
			usleep(rem * 1000 / 2);
		else
		{
			while ((get_time() - start) < ms)
				;
		}
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	result;
	int		t;

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

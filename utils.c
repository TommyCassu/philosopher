/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:00:47 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/06 19:39:08 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long usec, t_info *infos)
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = get_time();
	while (get_time() - start < usec)
	{
		if (infos->end_simulation == true)
			return ;
		elapsed = get_time() - start;
		rem = usec - elapsed;

		if (rem > 1e3)
			usleep(usec/2);
		else
		{
			while (get_time() - start < usec)
				;
		}
	}
}

long	get_time()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

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

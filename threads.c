/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:43:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/03 02:20:49 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table)
{
	int	i;
	
	i = 0;
	table->start_simulation = get_timestamp();
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].thread_id, NULL, philo_life, &table->philos[i]);
		i++;
	}
	return ;
}


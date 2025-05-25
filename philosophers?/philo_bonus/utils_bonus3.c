/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:09:24 by abkhefif          #+#    #+#             */
/*   Updated: 2025/05/25 18:05:44 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*meal_checker(void *arg)
{
	t_philodata	*data;
	int			finished;
	int			i;

	data = (t_philodata *)arg;
	finished = 0;
	if (data->must_eat <= 0)
		return (NULL);
	while (finished < data->philo_nb)
	{
		sem_wait(data->finished_eating_sem);
		finished++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (data->philosophers[i].pid > 0)
			kill(data->philosophers[i].pid, SIGTERM);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:15:58 by abkhefif          #+#    #+#             */
/*   Updated: 2025/05/18 14:45:50 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

int	check_simulation_status_bonus(t_philodata *data)
{
	int	status;

	if (sem_trywait(data->end_sem) == 0)
	{
		sem_post(data->end_sem);
		return (0);
	}
	sem_wait(data->status_sem);
	status = data->simulation_running;
	sem_post(data->status_sem);
	return (status);
}

void	cleanup_resources(t_philodata *philo_data)
{
	sem_close(philo_data->finished_eating_sem);  // ✅ AJOUTER
	sem_unlink("/finished_eating"); 
	sem_close(philo_data->simulation_sem);
	sem_close(philo_data->forks_sem);
	sem_close(philo_data->write_sem);
	sem_close(philo_data->status_sem);
	sem_close(philo_data->meal_sem);
	sem_close(philo_data->end_sem); 
	sem_unlink("/simulation");
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/status");
	sem_unlink("/meal");
	sem_unlink("/end");
	if (philo_data->forks)
		free(philo_data->forks);
	free(philo_data->philosophers);
	free(philo_data);
}

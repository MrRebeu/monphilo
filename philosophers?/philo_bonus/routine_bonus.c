/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:28 by abkhefif          #+#    #+#             */
/*   Updated: 2025/05/25 18:41:41 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	eat(t_philo *philo, long long *last_meal_time)
{
	t_philodata	*philo_data;

	philo_data = philo->philo_data;
	print_status(philo_data, philo->id, "is eating");
	*last_meal_time = get_time_ms();
	sem_wait(philo_data->status_sem);
	philo->last_meal_time = *last_meal_time;
	sem_post(philo_data->status_sem);
	ft_sleep(philo_data->time_to_eat);
	philo->meals_eaten++;
	if (philo_data->must_eat > 0 && philo->meals_eaten >= philo_data->must_eat)
	{
		sem_post(philo_data->forks_sem);
		sem_post(philo_data->forks_sem);
		sem_post(philo_data->finished_eating_sem);
		return (0);
	}
	sem_post(philo_data->forks_sem);
	sem_post(philo_data->forks_sem);
	return (1);
}

void	*death_checker(void *arg)
{
	t_philo		*philo;
	t_philodata	*data;

	philo = (t_philo *)arg;
	data = philo->philo_data;
	while (1)
	{
		sem_wait(data->status_sem);
		if (get_time_ms() - philo->last_meal_time > data->time_to_die)
		{
			sem_post(data->status_sem);
			sem_wait(data->write_sem);
			printf("%lld %d died\n", get_time_ms() - data->start_time,
				philo->id);
			exit(1);
		}
		sem_post(data->status_sem);
		usleep(100);
	}
	return (NULL);
}

void	take_forks(t_philo *philo, long long *last_meal_time)
{
	t_philodata	*philo_data;

	philo_data = philo->philo_data;
	(void)last_meal_time;
	if (philo->id % 2 == 0)
	{
		sem_wait(philo_data->forks_sem);
		print_status(philo_data, philo->id, "has taken a fork");
		sem_wait(philo_data->forks_sem);
		print_status(philo_data, philo->id, "has taken a fork");
	}
	else
	{
		sem_wait(philo_data->forks_sem);
		print_status(philo_data, philo->id, "has taken a fork");
		sem_wait(philo_data->forks_sem);
		print_status(philo_data, philo->id, "has taken a fork");
	}
}

void	sleep_and_think(t_philo *philo, long long *last_meal_time)
{
	t_philodata	*philo_data;

	philo_data = philo->philo_data;
	if (get_time_ms() - *last_meal_time > philo_data->time_to_die)
	{
		sem_wait(philo_data->write_sem);
		printf("%lld %d died\n", get_time_ms() - philo_data->start_time,
			philo->id);
		sem_post(philo_data->write_sem);
		sem_post(philo_data->end_sem);
		return ;
	}
	print_status(philo_data, philo->id, "is sleeping");
	ft_sleep(philo_data->time_to_sleep);
	print_status(philo_data, philo->id, "is thinking");
}

void	philosopher_routine_bonus(t_philo *philo)
{
	t_philodata	*philo_data;
	long long	last_meal_time;
	pthread_t	death_thread;

	philo_data = philo->philo_data;
	philo->last_meal_time = get_time_ms();
	last_meal_time = philo->last_meal_time;
	if (pthread_create(&death_thread, NULL, death_checker, philo) != 0)
		exit(1);
	pthread_detach(death_thread);
	if (philo->id % 2 == 0)
        usleep(philo_data->time_to_eat * 500);;
	while (1)
    {
       if (check_end_signal(philo_data))
            break ;
        take_forks(philo, &last_meal_time);
        if (!eat(philo, &last_meal_time))  // ← Mise à jour ici seulement
            break ;
        sleep_and_think(philo, &last_meal_time);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:28 by abkhefif          #+#    #+#             */
/*   Updated: 2025/05/18 14:44:02 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void take_forks(t_philo *philo, long long *last_meal_time)
{
    t_philodata *philo_data = philo->philo_data;
    
    // ✅ Vérifier AVANT de prendre les fourchettes
    if (get_time_ms() - *last_meal_time > philo_data->time_to_die)
    {
        sem_wait(philo_data->write_sem);
        printf("%lld %d died\n", get_time_ms() - philo_data->start_time, philo->id);
        sem_post(philo_data->write_sem);
        exit(1);
    }
    
    sem_wait(philo_data->forks_sem);
    
    // ✅ Vérifier APRÈS avoir pris la première fourchette
    if (get_time_ms() - *last_meal_time > philo_data->time_to_die)
    {
        sem_post(philo_data->forks_sem); // Libérer la fourchette
        sem_wait(philo_data->write_sem);
        printf("%lld %d died\n", get_time_ms() - philo_data->start_time, philo->id);
        sem_post(philo_data->write_sem);
        exit(1);
    }
    
    print_status(philo_data, philo->id, "has taken a fork");
    sem_wait(philo_data->forks_sem);
    print_status(philo_data, philo->id, "has taken a fork");
}

int	eat(t_philo *philo, long long *last_meal_time)
{
	t_philodata	*philo_data;

	philo_data = philo->philo_data;
	print_status(philo_data, philo->id, "is eating");
	*last_meal_time = get_time_ms();
	ft_sleep(philo_data->time_to_eat);
	philo->meals_eaten++;
	if (philo_data->must_eat > 0 && philo->meals_eaten >= philo_data->must_eat)
	{
		sem_post(philo_data->forks_sem);
		sem_post(philo_data->forks_sem);
		return (0);
	}
	sem_post(philo_data->forks_sem);
	sem_post(philo_data->forks_sem);
	return (1);
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

int	check_end_signal(t_philodata *philo_data)
{
	if (sem_trywait(philo_data->end_sem) == 0)
	{
		sem_post(philo_data->end_sem);
		return (1);
	}
	return (0);
}

void	philosopher_routine_bonus(t_philo *philo)
{
	t_philodata	*philo_data;
	long long	last_meal_time;

	philo_data = philo->philo_data;
	last_meal_time = philo_data->start_time;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (check_end_signal(philo_data))
			break ;
		if (get_time_ms() - last_meal_time > philo_data->time_to_die)
		{
			sem_wait(philo_data->write_sem);
			printf("%lld %d died\n", get_time_ms() - philo_data->start_time,
				philo->id);
			sem_post(philo_data->write_sem);
			sem_post(philo_data->end_sem);
			break ;
		}
		take_forks(philo, &last_meal_time);
		if (!eat(philo, &last_meal_time))
			break ;
		sleep_and_think(philo, &last_meal_time);
	}
}

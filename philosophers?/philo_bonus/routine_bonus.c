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

void *meal_checker(void *arg)
{
    t_philodata *data = (t_philodata *)arg;
    int finished = 0;
    
    if (data->must_eat <= 0)
        return (NULL);
    
    while (finished < data->philo_nb)
    {
        sem_wait(data->finished_eating_sem);
        finished++;
    }
    
    // Tous ont fini de manger - tuer tous les processus
    int i = 0;
    while (i < data->philo_nb)
    {
        if (data->philosophers[i].pid > 0)
            kill(data->philosophers[i].pid, SIGTERM);
        i++;
    }
    
    return (NULL);
}

int eat(t_philo *philo, long long *last_meal_time)
{
    t_philodata *philo_data;

    philo_data = philo->philo_data;
    print_status(philo_data, philo->id, "is eating");
    
    *last_meal_time = get_time_ms();
    
    // ✅ Aussi mettre à jour dans la structure pour le thread death_checker
    sem_wait(philo_data->status_sem);
    philo->last_meal_time = *last_meal_time;
    sem_post(philo_data->status_sem);
    
    ft_sleep(philo_data->time_to_eat);
    
    philo->meals_eaten++;
    if (philo_data->must_eat > 0 && philo->meals_eaten >= philo_data->must_eat)
    {
        sem_post(philo_data->forks_sem);
        sem_post(philo_data->forks_sem);
        sem_post(philo_data->finished_eating_sem); // ✅ Signaler qu'on a fini
        return (0);
    }
    
    sem_post(philo_data->forks_sem);
    sem_post(philo_data->forks_sem);
    return (1);
}

void *death_checker(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_philodata *data = philo->philo_data;
    
    while (1)
    {
        sem_wait(data->status_sem);
        if (get_time_ms() - philo->last_meal_time > data->time_to_die)
        {
            sem_post(data->status_sem);
            sem_wait(data->write_sem);
            printf("%lld %d died\n", get_time_ms() - data->start_time, philo->id);
            // Ne pas faire sem_post sur write_sem pour bloquer les autres prints
            exit(1);
        }
        sem_post(data->status_sem);
        usleep(1000);
    }
    return (NULL);
}

void take_forks(t_philo *philo, long long *last_meal_time)
{
    t_philodata *philo_data = philo->philo_data;
    
    // Pas de vérification de mort ici, le thread death_checker s'en occupe
    sem_wait(philo_data->forks_sem);
    print_status(philo_data, philo->id, "has taken a fork");
    sem_wait(philo_data->forks_sem);
    print_status(philo_data, philo->id, "has taken a fork");
    
    (void)last_meal_time; // Pour éviter le warning unused
}

void release_forks(t_philo *philo)
{
    sem_post(philo->philo_data->forks_sem);
    sem_post(philo->philo_data->forks_sem);
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

void philosopher_routine_bonus(t_philo *philo)
{
    t_philodata *philo_data;
    long long last_meal_time;
    pthread_t death_thread; // ✅ Variable locale au lieu de dans la structure
    
    philo_data = philo->philo_data;
    philo->last_meal_time = get_time_ms();
    last_meal_time = philo->last_meal_time;
    
    // ✅ Créer le thread de vérification de mort
    if (pthread_create(&death_thread, NULL, death_checker, philo) != 0)
        exit(1);
    pthread_detach(death_thread);
    
    if (philo->id % 2 == 0)
        usleep(1000);
        
    while (1)
    {
        if (check_end_signal(philo_data))
            break;
            
        take_forks(philo, &last_meal_time);
        
        // ✅ Mettre à jour last_meal_time dans la structure avec protection
        sem_wait(philo_data->status_sem);
        philo->last_meal_time = get_time_ms();
        last_meal_time = philo->last_meal_time;
        sem_post(philo_data->status_sem);
        
        if (!eat(philo, &last_meal_time))
            break;
            
        sleep_and_think(philo, &last_meal_time); // ✅ Passer le 2ème paramètre
    }
}
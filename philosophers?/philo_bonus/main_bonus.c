/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:25 by abkhefif          #+#    #+#             */
/*   Updated: 2025/05/18 14:47:07 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_philosopher_death(t_philodata *data, int i)
{
	long long	time_since_last_meal;
	int			should_die;
	long long	current_time;

	current_time = get_time_ms();
	sem_wait(data->status_sem);
	time_since_last_meal = current_time - data->philosophers[i].last_meal_time;
	should_die = time_since_last_meal > data->time_to_die;
	sem_post(data->status_sem);
	if (should_die)
	{
		sem_wait(data->write_sem);
		printf("%lld %d died\n", get_time_ms() - data->start_time, i + 1);
		sem_post(data->write_sem);
		sem_post(data->end_sem);
		return (1);
	}
	return (0);
}

void	*monitor_philosophers_bonus(void *arg)
{
	int			i;
	t_philodata	*data;
	int			j;

	data = (t_philodata *)arg;
	while (check_simulation_status_bonus(data))
	{
		i = 0;
		while (i < data->philo_nb)
		{
			if (check_philosopher_death(data, i))
			{
				j = 0;
				while (j < data->philo_nb)
				{
					if (data->philosophers[j].pid > 0)
						kill(data->philosophers[j].pid, SIGTERM);
					j++;
				}
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int begin_simulation_bonus(t_philo *philosophers, t_philodata *philo_data, pid_t *pids)
{
    (void)philosophers;  // ✅ Éviter le warning
    int i;
    pthread_t meal_thread;
    
    // Cas 1 philosophe...
    
    // Créer le thread meal_checker si nécessaire
    if (philo_data->must_eat > 0)
    {
        pthread_create(&meal_thread, NULL, meal_checker, philo_data);
        pthread_detach(meal_thread);
    }
    
    // Fork tous les philosophes
    i = 0;
    while (i < philo_data->philo_nb)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            philosopher_routine_bonus(&philo_data->philosophers[i]);
            exit(0);
        }
        i++;
    }
    
    // Attendre qu'un processus se termine
    waitpid(-1, NULL, 0);
    
    // Tuer tous les autres
    i = 0;
    while (i < philo_data->philo_nb)
    {
        if (pids[i] > 0)
            kill(pids[i], SIGTERM);
        i++;
    }
    
    // Attendre que tous se terminent
    while (wait(NULL) > 0);
    
    return (0);
}

int main(int ac, char **av)
{
    t_philodata *philo_data;
    pid_t *pids;  // ✅ SEUL ajout
    int i;

    // ✅ VOTRE code existant - INCHANGÉ
    i = 1;
    if (ac < 5 || ac > 6)
        return (printf("Error: wrong number of arguments\n"), 1);
    while (i < ac)
    {
        if (!is_valid_number(av[i]))
            return (printf("Error: argument %d is not a valid number\n", i), 1);
        i++;
    }
    if (ft_atoi(av[1]) <= 0)
        return (printf("Error: number of philosophers must be positive\n"), 1);
    
    philo_data = malloc(sizeof(t_philodata));
    if (!philo_data)
        return (1);
    if (!init_data_philo_bonus(ac, av, philo_data))
    {
        free(philo_data);
        return (1);
    }
    init_philo_bonus(philo_data, philo_data->philosophers);

    // ✅ NOUVEAU : Juste stocker les PIDs
    pids = malloc(sizeof(pid_t) * philo_data->philo_nb);
    
    // ✅ VOTRE fonction existante - on va juste la modifier légèrement
    begin_simulation_bonus(philo_data->philosophers, philo_data, pids);
    
    free(pids);
    cleanup_resources(philo_data);
    return (0);
}
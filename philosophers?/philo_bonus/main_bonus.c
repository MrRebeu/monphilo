/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <abkhefif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:25 by abkhefif          #+#    #+#             */
/*   Updated: 2025/05/25 18:01:17 by abkhefif         ###   ########.fr       */
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

void	fork_philosophers(t_philodata *philo_data, pid_t *pids)
{
	int	i;

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
}

void	terminate_all_processes(t_philodata *philo_data, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < philo_data->philo_nb)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGTERM);
		i++;
	}
	while (wait(NULL) > 0)
		;
}

int	begin_simulation_bonus(t_philo *philosophers, t_philodata *philo_data,
		pid_t *pids)
{
	pthread_t	meal_thread;

	(void)philosophers;
	if (philo_data->must_eat > 0)
	{
		pthread_create(&meal_thread, NULL, meal_checker, philo_data);
		pthread_detach(meal_thread);
	}
	fork_philosophers(philo_data, pids);
	waitpid(-1, NULL, 0);
	terminate_all_processes(philo_data, pids);
	return (0);
}

int	main(int ac, char **av)
{
	t_philodata	*philo_data;
	pid_t		*pids;

	if (!validate_arguments(ac, av))
		return (1);
	philo_data = malloc(sizeof(t_philodata));
	if (!philo_data)
		return (1);
	if (!init_data_philo_bonus(ac, av, philo_data))
	{
		free(philo_data);
		return (1);
	}
	init_philo_bonus(philo_data, philo_data->philosophers);
	pids = malloc(sizeof(pid_t) * philo_data->philo_nb);
	begin_simulation_bonus(philo_data->philosophers, philo_data, pids);
	free(pids);
	cleanup_resources(philo_data);
	return (0);
}

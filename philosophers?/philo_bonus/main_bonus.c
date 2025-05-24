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
		usleep(900);
	}
	return (NULL);
}

int	begin_simulation_bonus(t_philo *philosophers, t_philodata *philo_data)
{
	int	i;

	(void)philosophers;
    if (philo_data->philo_nb == 1)
	{
		philo_data->philosophers[0].pid = fork();
		if (philo_data->philosophers[0].pid == 0)
		{
			print_status(philo_data, 1, "has taken a fork");
			ft_sleep(philo_data->time_to_die);
			sem_wait(philo_data->write_sem);
			printf("%lld %d died\n", get_time_ms() - philo_data->start_time, 1);
			sem_post(philo_data->write_sem);
			exit(1);
		}
		waitpid(philo_data->philosophers[0].pid, NULL, 0);
		return (0);
	}
	i = 0;
	while (i < philo_data->philo_nb)
	{
		philo_data->philosophers[i].pid = fork();
		if (philo_data->philosophers[i].pid == 0)
		{
			philosopher_routine_bonus(&philo_data->philosophers[i]);
			exit(0);
		}
		if (philo_data->philosophers[i].pid < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philo_data->philo_nb)
	{
		waitpid(philo_data->philosophers[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philodata	*philo_data;
	int			result;
	int			i;

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
	if (ac < 5 || ac > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	philo_data = malloc(sizeof(t_philodata));
	if (!philo_data)
		return (1);
	if (!init_data_philo_bonus(ac, av, philo_data))
	{
		free(philo_data);
		return (1);
	}
	init_philo_bonus(philo_data, philo_data->philosophers);
	result = begin_simulation_bonus(philo_data->philosophers, philo_data);
	cleanup_resources(philo_data);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:59:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 21:05:47 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_routine(void *void_philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)void_philosopher;
	table = philo->table;
	while (!check_stop_condition(table))
	{
		if (check_eat_times(table, philo))
			break ;
		if (table->number_of_philosophers == 1)
			eat_action_solo(table, philo);
		else
			philo_eats(philo);
		if (check_stop_condition(table))
			break ;
		philo_sleeps(philo);
		if (check_stop_condition(table))
			break ;
		action_print(philo->table, philo->id, "is thinking");
	}
	return (NULL);
}

void	cleanup_and_exit(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&(table->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(table->meal_check));
	pthread_mutex_destroy(&(table->writing));
}

void	philo_sleeps(t_philo *philo)
{
	action_print(philo->table, philo->id, "is sleeping");
	smart_sleep(philo->table->time_to_sleep, philo->table);
}

int	dinner_time(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = table->philosopher;
	table->start_meal_time = timestamp();
	while (i < table->number_of_philosophers)
	{
		philos[i].last_meal = table->start_meal_time;
		if (pthread_create(&(philos[i].thread_id), NULL, philosopher_routine,
				&(philos[i])))
			return (1);
		i++;
	}
	monitor_philosophers(table, philos);
	cleanup_and_exit(table, philos);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:59:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 20:33:14 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_routine(void *void_philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)void_philosopher;
	table = philo->table;
	while (!(table->dead_count) && !(table->all_ate))
	{
		pthread_mutex_lock(&(table->meal_check));
		if (table->eat_times != -1 && philo->eat_count >= table->eat_times)
		{
			pthread_mutex_unlock(&(table->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(table->meal_check));
		philo_eats(philo);
		if (table->all_ate || table->dead_count)
			break ;
		philo_sleeps(philo);
		if (table->all_ate || table->dead_count)
			break ;
		action_print(table, philo->id, "is thinking");
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

int	dinner_time(t_table *table)
{
	int			i;
	t_philo		*philos;

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

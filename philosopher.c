/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:59:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 19:14:20 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philosopher_routine(void *void_philosopher)
{
    t_philo *philo = (t_philo *)void_philosopher;
    t_table *table = philo->table;

    // Stagger start times to prevent contention

    
    while (!(table->dead_count) && !(table->all_ate))
    {
        pthread_mutex_lock(&(table->meal_check));
        if (table->eat_times != -1 && philo->eat_count >= table->eat_times)
        {
            pthread_mutex_unlock(&(table->meal_check));
            break;
        }
        pthread_mutex_unlock(&(table->meal_check));

        philo_eats(philo);

        if (table->all_ate || table->dead_count)
            break;

        philo_sleeps(philo);

        if (table->all_ate || table->dead_count)
            break;
        action_print(table, philo->id, "is thinking");
    }
    return (NULL);
}

void cleanup_and_exit(t_table *table, t_philo *philos)
{
    int i = 0;

    // Wait for all threads to finish
    while (i < table->number_of_philosophers) {
        pthread_join(philos[i].thread_id, NULL);
        i++;
    }

    i = 0; // Reset the counter

    // Destroy mutexes
    while (i < table->number_of_philosophers) {
        pthread_mutex_destroy(&(table->forks[i]));
        i++;
    }

    pthread_mutex_destroy(&(table->meal_check));
    pthread_mutex_destroy(&(table->writing));
}


int dinner_time(t_table *table)
{
    int i = 0;
    t_philo *philos = table->philosopher;

    table->start_meal_time = timestamp();

    // Create philosopher threads
    while (i < table->number_of_philosophers)
    {
        philos[i].last_meal = table->start_meal_time;
        if (pthread_create(&(philos[i].thread_id), NULL, philosopher_routine, &(philos[i])))
            return (1);
        i++; // Increment the counter
    }

    // Monitor the philosophers
    monitor_philosophers(table, philos);

    // Cleanup and exit
    cleanup_and_exit(table, philos);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:59:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 15:45:40 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Philosopher takes forks and eats.
 * Handles the special case when there is only one philosopher.
 */
void philo_eats(t_philo *philo)
{
    t_table *table = philo->table;

    pthread_mutex_lock(&(table->forks[philo->left_fork]));
    action_print(table, philo->id, "has taken a fork");
    if (philo->left_fork == philo->right_fork)
    {
        while (!(table->dead_count))
            usleep(1000);
        pthread_mutex_unlock(&(table->forks[philo->left_fork]));
        return;
    }
    pthread_mutex_lock(&(table->forks[philo->right_fork]));
    action_print(table, philo->id, "has taken a fork");
    pthread_mutex_lock(&(table->meal_check));
    action_print(table, philo->id, "is eating");
    philo->last_meal = timestamp();
    philo->eat_count++;
    pthread_mutex_unlock(&(table->meal_check));
    smart_sleep(table->time_to_eat, table);
    pthread_mutex_unlock(&(table->forks[philo->left_fork]));
    pthread_mutex_unlock(&(table->forks[philo->right_fork]));
}

/**
 * Philosopher sleeps.
 */
void philo_sleeps(t_philo *philo)
{
    t_table *table = philo->table;

    action_print(table, philo->id, "is sleeping");
    smart_sleep(table->time_to_sleep, table);
}

/**
 * Philosopher thinks.
 */
void philo_thinks(t_philo *philo)
{
    t_table *table = philo->table;

    action_print(table, philo->id, "is thinking");
}

/**
 * The routine that each philosopher thread runs.
 * Philosophers perform actions: eat, sleep, think.
 */
void *philosopher_routine(void *void_philosopher)
{
    t_philo *philo = (t_philo *)void_philosopher;
    t_table *table = philo->table;

    // Stagger start times to prevent contention
    if (philo->id % 2)
        usleep(15000);

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
        philo_thinks(philo);
    }
    return (NULL);
}

/**
 * Checks if any philosopher has died.
 * Returns 1 if a philosopher has died, 0 otherwise.
 */
int check_philosopher_death(t_table *table, t_philo *philos)
{
    int i = 0; 

    while (i < table->number_of_philosophers)
    {
        pthread_mutex_lock(&(table->meal_check));
        if (time_diff(philos[i].last_meal, timestamp()) > table->time_to_die)
        {
            action_print(table, philos[i].id, "died");
            table->dead_count = 1;
            pthread_mutex_unlock(&(table->meal_check));
            return 1;
        }
        pthread_mutex_unlock(&(table->meal_check));
        i++; // Increment the counter
    }
    return 0;
}

/**
 * Checks if all philosophers have eaten the required number of times.
 * Returns 1 if all have eaten enough, 0 otherwise.
 */
int check_all_ate(t_table *table, t_philo *philos)
{
    int i = 0;

    if (table->eat_times == -1)
        return 0;

    while (i < table->number_of_philosophers)
    {
        pthread_mutex_lock(&(table->meal_check));
        if (philos[i].eat_count < table->eat_times)
        {
            pthread_mutex_unlock(&(table->meal_check));
            return 0;
        }
        pthread_mutex_unlock(&(table->meal_check));
        i++; // Increment the counter
    }
    table->all_ate = 1;
    return 1;
}

/**
 * Monitors the philosophers to check for death or completion.
 */
void monitor_philosophers(t_table *table, t_philo *philos)
{
    while (!(table->dead_count) && !(table->all_ate))
    {
        if (check_philosopher_death(table, philos))
            break;

        if (check_all_ate(table, philos))
            break;

        usleep(1000); // Sleep briefly to reduce CPU usage
    }
}

/**
 * Waits for all threads to finish and cleans up mutexes.
 */
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

/**
 * Starts the simulation by creating philosopher threads and monitoring them.
 */
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
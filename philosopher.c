/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:59:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 12:21:30 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    while (1) {
        // Think
        printf("Philosopher %d is thinking\n", philo->id + 1); 

        // Take forks (with deadlock prevention)
        pthread_mutex_lock(&table->forks[philo->left_fork]);
        printf("Philosopher %d has taken left fork %d\n", philo->id + 1, philo->left_fork + 1);
        pthread_mutex_lock(&table->forks[philo->right_fork]);
        printf("Philosopher %d has taken right fork %d\n", philo->id + 1, philo->right_fork + 1);

        // Eat
        printf("Philosopher %d is eating\n", philo->id + 1);
        usleep(table->time_to_eat * 1000); // Simulate eating
        philo->eat_count++;

        // Release forks
        pthread_mutex_unlock(&table->forks[philo->right_fork]);
        pthread_mutex_unlock(&table->forks[philo->left_fork]);

        // Sleep
        printf("Philosopher %d is sleeping\n", philo->id + 1);
        usleep(table->time_to_sleep * 1000); // Simulate sleeping
    }

    return (NULL);
}
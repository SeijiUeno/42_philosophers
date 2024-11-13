/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:54:59 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 19:35:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void take_forks(t_philo *philo) {
    t_table *table = philo->table;

    pthread_mutex_lock(&(table->forks[philo->right_fork]));
    action_print(table, philo->id, "has taken a fork");
    pthread_mutex_lock(&(table->forks[philo->left_fork]));
    action_print(table, philo->id, "has taken a fork");
}

static void release_forks(t_philo *philo) {
    t_table *table = philo->table;
    
    pthread_mutex_unlock(&(table->forks[philo->left_fork]));
    pthread_mutex_unlock(&(table->forks[philo->right_fork]));
}

static void eat_action(t_philo *philo) {
    t_table *table = philo->table;
    
    pthread_mutex_lock(&(table->meal_check));
    action_print(table, philo->id, "is eating");
    philo->last_meal = timestamp();
    philo->eat_count++;
    pthread_mutex_unlock(&(table->meal_check));
    smart_sleep(table->time_to_eat, table);
}

void philo_eats(t_philo *philo) 
{
    take_forks(philo);
    eat_action(philo);
    release_forks(philo);
}

void philo_sleeps(t_philo *philo) {
    action_print(philo->table, philo->id, "is sleeping");
    smart_sleep(philo->table->time_to_sleep, philo->table);
}

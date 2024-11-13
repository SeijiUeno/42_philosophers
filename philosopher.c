/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:59:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 13:56:32 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void philo_eats(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    pthread_mutex_lock(&(table->forks[philo->left_fork]));
    action_print(table, philo->id, "has taken a fork");
    pthread_mutex_lock(&(table->forks[philo->right_fork]));
    action_print(table, philo->id, "has taken a fork");
    pthread_mutex_lock(&(table->meal_check));
    action_print(table, philo->id, "is eating");
    philo->last_meal = timestamp();
    pthread_mutex_unlock(&(table->meal_check));
    smart_sleep(table->time_to_eat, table);
    (philo->eat_count)++;
    pthread_mutex_unlock(&(table->forks[philo->left_fork]));
    pthread_mutex_unlock(&(table->forks[philo->right_fork]));
}

void *p_thread(void *void_philosopher)
{
    int     i;
    t_philo *philo;
    t_table *table;

    i = 0;
    philo = (t_philo *)void_philosopher;
    table = philo->table;
    if (philo->id % 2)
        usleep(15000);
    while (!(table->dead_count))
    {
        philo_eats(philo);
        if (table->all_ate)
            break;
        action_print(table, philo->id, "is sleeping");
        smart_sleep(table->time_to_sleep, table);
        action_print(table, philo->id, "is thinking");
        i++;
    }
    return (NULL);
}

void exit_launcher(t_table *rules, t_philo *philos)
{
    int i;

    i = -1;
    while (++i < rules->number_of_philosophers)
        pthread_join(philos[i].thread_id, NULL);
    i = -1;
    while (++i < rules->number_of_philosophers)
        pthread_mutex_destroy(&(rules->forks[i]));
    pthread_mutex_destroy(&(rules->meal_check));
    pthread_mutex_destroy(&(rules->writing));
}

void death_checker(t_table *r, t_philo *p)
{
    int i;

    while (!(r->all_ate))
    {
        i = -1;
        while (++i < r->number_of_philosophers && !(r->dead_count))
        {
            pthread_mutex_lock(&(r->meal_check));
            if (time_diff(p[i].last_meal, timestamp()) > r->time_to_die)
            {
                action_print(r, i, "died");
                r->dead_count = 1;
            }
            pthread_mutex_unlock(&(r->meal_check));
            usleep(100);
        }
        if (r->dead_count)
            break;
        i = 0;
        while (r->eat_times != -1 && i < r->number_of_philosophers && p[i].eat_count >= r->eat_times)
            i++;
        if (i == r->number_of_philosophers)
            r->all_ate = 1;
    }
}

int dinner_time(t_table *table)
{
    int     i;
    t_philo *philo;

    i = 0;
    philo = table->philosopher;
    table->start_meal_time = timestamp();
    while (i < table->number_of_philosophers)
    {
        philo[i].last_meal = table->start_meal_time; // Initialize last_meal
        if (pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i])))
            return (1);
        i++;
    }
    death_checker(table, table->philosopher);
    exit_launcher(table, philo);
    return (0);
}

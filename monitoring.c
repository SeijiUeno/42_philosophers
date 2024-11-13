/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:00:42 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 19:01:41 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int check_philosopher_death(t_table *table, t_philo *philos) {
    int i = 0;
    while (i < table->number_of_philosophers) {
        pthread_mutex_lock(&(table->meal_check));
        if (timestamp() - philos[i].last_meal > table->time_to_die) {
            action_print(table, philos[i].id, "died");
            table->dead_count = 1;
            pthread_mutex_unlock(&(table->meal_check));
            return 1;
        }
        pthread_mutex_unlock(&(table->meal_check));
        i++;
    }
    return 0;
}

int check_all_ate(t_table *table, t_philo *philos) {
    int i = 0;
    if (table->eat_times == -1)
        return 0;
    while (i < table->number_of_philosophers) {
        pthread_mutex_lock(&(table->meal_check));
        if (philos[i].eat_count < table->eat_times) {
            pthread_mutex_unlock(&(table->meal_check));
            return 0;
        }
        pthread_mutex_unlock(&(table->meal_check));
        i++;
    }
    table->all_ate = 1;
    return 1;
}

void monitor_philosophers(t_table *table, t_philo *philos) {
    while (!(table->dead_count) && !(table->all_ate)) {
        if (check_philosopher_death(table, philos) || check_all_ate(table, philos))
            break;
        usleep(100);
    }
}
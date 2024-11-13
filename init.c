/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:58:32 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 12:09:52 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void philos_setter(t_table *table)
{
    int guests;
    int i;
    
    guests = table->number_of_philosophers;
    i = guests;
    while (--i >= 0)
    {
        table->philosopher[i].id = i;
        table->philosopher[i].eat_count = 0;
        table->philosopher[i].left_fork = i;
        table->philosopher[i].right_fork = (i+1) % guests;
        table->philosopher[i].last_meal = 0;
        table->philosopher[i].table = table;
    }
}

static int init_table_safeguard(t_table *table)
{
    int i;

    if (pthread_mutex_init(&table->writing, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&table->meal_check, NULL) != 0)
        return (1);
    i = table->number_of_philosophers;
    while (--i >= 0)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
            return (1);
    }
    return (0);
}

static int basic_rules_checker(t_table *table) {
    if (table->number_of_philosophers < 2) {
        fprintf(stderr, "Error: Need at least 2 philosophers.\n");
        return (1);
    }
    if (table->time_to_eat < 0) {
        fprintf(stderr, "Error: time_to_eat cannot be negative.\n");
        return (1);
    }
    if (table->time_to_sleep < 0) {
        fprintf(stderr, "Error: time_to_sleep cannot be negative.\n");
        return (1);
    }
    if (table->number_of_philosophers > 200) {
        fprintf(stderr, "Error: Maximum 200 philosophers allowed.\n");
        return (1);
    }
    return (0);
}

int init_table(t_table *table) {
    if (basic_rules_checker(table) || init_table_safeguard(table)) {
        return (1);
    }
    philos_setter(table);
    return (0);
}
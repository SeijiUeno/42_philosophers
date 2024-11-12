/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initializer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:58:32 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/12 17:44:29 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int philos_setter(t_table *table)
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
    return (0);
}

int init_table_safeguard(t_table *table)
{
    int i;
    
    if (phtread_mutex_init(&(table->writing), NULL))
        return (1);
    if (phtread_mutex_init(&(table->meal_check, NULL)))
        return (1);
    i = table->number_of_philosophers;
    while (--i >= 0)
    {
        if (phtread_mutex_init(&(table->fork[i], NULL)))
            return (1);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_initializer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:01:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/12 18:14:18 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static  int basic_rules_checker(t_table *table);

int init_table(t_table *table)
{
    if (!basic_rules_checker(table) || !init_table_safeguard(table))
        return (1);
    philos_setter(table);
}

static  int basic_rules_checker(t_table *table)
{
    if (table->number_of_philosophers < 2 || table->time_eat < 0
		|| table->time_to_sleep < 0 || table->number_of_philosophers > 200)
		return (1)
    return (0);
}
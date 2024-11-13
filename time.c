/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:00:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 14:15:03 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long timestamp(void)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long time_diff(long long past, long long pres)
{
    return (pres - past);
}

void action_print(t_table *rules, int id, char *action)
{
    long long current_time;

    pthread_mutex_lock(&(rules->writing));

    current_time = timestamp() - rules->start_meal_time; 
    if (!(rules->dead_count))
        printf("%lld %d %s\n", current_time, id + 1, action);

    pthread_mutex_unlock(&(rules->writing));
}

void smart_sleep(int duration, t_table *table)
{
    long long start_time;

    start_time = timestamp();
    while (!(table->dead_count))
    {
        if (time_diff(start_time, timestamp()) >= duration)
            break;
        usleep(100);
    }
}
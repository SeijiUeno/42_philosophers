/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:34:45 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 11:02:37 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"


int validate_input(int argc, char *input[]) {
    int i;
    
    if (argc < 5 || argc > 6) {
        fprintf(stderr, "Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n", input[0]);
        return (1);
    }
    i = 1;
    while (i < argc) {
        if (!only_digits(input[i])) {
            fprintf(stderr, "%s: Input ERROR\n", input[0]);
            return (1);
        }
        i++;
    }
    return (0);
}

void load_input(t_table *holder, char *input[]) {
    holder->number_of_philosophers = ft_atoi(input[1]);
    holder->time_to_die = ft_atoi(input[2]);
    holder->time_to_eat = ft_atoi(input[3]);
    holder->time_to_sleep = ft_atoi(input[4]);
    holder->all_ate = 0;
    holder->dead_count = 0;
    if (input[5]) {
        holder->eat_times = atoi(input[5]);
    } else {
        holder->eat_times = -1; 
    }
}
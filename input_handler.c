/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:34:45 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/11 17:03:17 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

int basic_check(int argc, char *input[])
{
    int i;
    int number;

    i = 1;
    if (argc < 5 || argc > 6)
    {
        fprintf(stderr, "Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n", input[0]);
        return (1);
    }
    while (i < argc)
    {
        if (!only_digits(input[i]))
        {
            fprintf(stderr, "%s: Input ERROR\n", input[0]);
            return (0);
        }
        number = ft_atoi(input[i]);
        if (i != 1 && number == (-1))
        {
            fprintf(stderr, "%s: Bigger than INT_MAX!\n", input[0]);
            return (0);
        }
        if (i == 1 && number <= 0)
        {
            fprintf(stderr, "%s: Number of Phiolosophers invalid!\n", input[0]);
            return (0);
        }
        i++;
    }
    return (1);
}

void load_input(t_init *holder, char *input[])
{
    holder->number_of_philosophers = ft_atoi(input[1]);
    holder->time_to_die = ft_atoi(input[2]);
    holder->time_to_eat = ft_atoi(input[3]);
    holder->time_to_sleep = ft_atoi(input[4]);

    // Check for the optional argument
    if (input[5])
        holder->eat_times = ft_atoi(input[5]);
    else
        holder->eat_times = (-1);
}
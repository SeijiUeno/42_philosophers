/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/11 16:11:06 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // fprintf funtion !forbidden to be removed WIP!

#define INT_MAX 2147483647
/*
    logs 
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

typedef struct init
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_times;
}t_init;

int isspace(int c) {
    if (c == ' ' || c == '\t' || c == '\n' || 
        c == '\r' || c == '\v' || c == '\f') 
        {
        return (1);
    }
    else 
    {
        return (0);
    }
}

int atoi(char *str)
{
	unsigned long int	    number;
	int						i;

    // add whitespaces check and negative?
	i = 0;
	number = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
    i = (int)number;
	return (i);
}

int only_digits(char *str)
{
	int	i;

	i = 0;
    while (isspace(str[i]))
    {
        i++;
    }
    if (str[0] == '\0')
        return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int basic_check(int argc, char *input[])
{
    int i;
    int number;

    i = 1;
    while (i < argc)
    {
        if (!only_digits(input[i]))
        {
            fprintf(stderr, "%s: Input ERROR\n", input[0]);
            return (0);
        }
        number = atoi(input[i]);
        if (i == 1 && number <= 0)
        {
            fprintf(stderr, "%s: Number of Phiolosophers invalid!\n", input[0]);
            return (0);
        }
        if (i != 1 && number == (-1))
        {
            fprintf(stderr, "%s: Negative Number ERROR\n", input[0]);
            return (0);
        }
        i++;
    }
    return (1);
}

void load_input(t_init *holder, char *input[])
{
    holder->number_of_philosophers = atoi(input[1]);
    holder->time_to_die = atoi(input[2]);
    holder->time_to_eat = atoi(input[3]);
    holder->time_to_sleep = atoi(input[4]);

    // Check for the optional argument
    if (input[5])
        holder->eat_times = atoi(input[5]);
    else
        holder->eat_times = (-1);
}

int main(int argc, char *argv[])
{
    t_init  holder;
    
    if (argc < 5 || argc > 6)
    {
        fprintf(stderr, "Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n", argv[0]);
        return (1);
    }
    if (!basic_check(argc, argv))
    {
        fprintf(stderr, "%s : Basic_Check ERROR\n", argv[0]);
        return (1);
    }
    load_input(&holder, argv);
    
}
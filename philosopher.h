/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:30:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 15:26:14 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define USE_ERROR "./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>\n"

/*
    Logs 
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

typedef struct s_table t_table; // Forward declaration
typedef struct s_philo t_philo;

struct s_philo
{
    int             id;
    int             eat_count;
    long long       last_meal;
    int             left_fork;
    int             right_fork;
    pthread_t       thread_id;
    t_table         *table; 
};

struct s_table
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             eat_times; 
    int             dead_count;
    int             all_ate;
    unsigned long   start_meal_time;
    t_philo         philosopher[201];
    pthread_mutex_t forks[201];
    pthread_mutex_t meal_check;
    pthread_mutex_t writing; 
};

int isspace(int c);
int ft_atoi(char *str);
int only_digits(char *str);
void ft_putstr_fd(char *s, int fd);

void load_input(t_table *holder, char *input[]);
int validate_input(int argc, char *input[]);

int init_table(t_table *table);

void *philosopher_routine(void *arg);

long long	time_diff(long long past, long long pres);
long long	timestamp(void);
void    action_print(t_table *rules, int id, char *string);

int dinner_time(t_table *table);

void cleanup_and_exit(t_table *table, t_philo *philos);
void monitor_philosophers(t_table *table, t_philo *philos);
int check_all_ate(t_table *table, t_philo *philos);
int check_philosopher_death(t_table *table, t_philo *philos);
void *philosopher_routine(void *void_philosopher);
void philo_thinks(t_philo *philo);
void philo_sleeps(t_philo *philo);
void philo_eats(t_philo *philo);

void smart_sleep(int duration, t_table *table);

#endif

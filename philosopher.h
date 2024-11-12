#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h> // fprintf function (forbidden to be removed WIP!)
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

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

typedef struct s_philo
{
    int             id;
    int             eat_count;
    long long       last_meal;
    int             left_fork;
    int             right_fork;
    pthread_t       thread_id;
    t_table         *table; 
}               t_philo;

typedef struct s_table
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             eat_times; 
    int             dead_count;
    int             finished_meals;
    unsigned long   start_meal_time;
    t_philo         philosopher[201];
    pthread_mutex_t forks[201];
    pthread_mutex_t meal_check;
    pthread_mutex_t writing; 
}               t_table;

int isspace(int c);
int ft_atoi(char *str);
int only_digits(char *str);
int basic_check(int argc, char *input[]);
void load_input(t_table *holder, char *input[]);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/11/13 12:30:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 21:08:38 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

=======
/*   Created: 2024/11/11 16:36:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/11 16:45:54 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:12 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h> // fprintf funtion !forbidden to be removed WIP!
# include <stdlib.h>
>>>>>>> main
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647
<<<<<<< HEAD

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct					s_philo
{
	int					id;
	int					eat_count;
	long long			last_meal;
	int					left_fork;
	int					right_fork;
	pthread_t			thread_id;
	t_table				*table;
};

struct					s_table
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_times;
	int					dead_count;
	int					all_ate;
	unsigned long		start_meal_time;
	t_philo				philosopher[201];
	pthread_mutex_t		forks[201];
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
};

int						isspace(int c);
int						ft_atoi(char *str);
int						only_digits(char *str);
void					ft_putstr_fd(char *s, int fd);
void					load_input(t_table *holder, char *input[]);
int						validate_input(int argc, char *input[]);
int						init_table(t_table *table);
void					*philosopher_routine(void *arg);
long long				time_diff(long long past, long long pres);
long long				timestamp(void);
void					action_print(t_table *rules, int id, char *string);
int						dinner_time(t_table *table);
void					cleanup_and_exit(t_table *table, t_philo *philos);
void					monitor_philosophers(t_table *table, t_philo *philos);
int						check_all_ate(t_table *table, t_philo *philos);
int						check_death(t_table *table, t_philo *philos);
void					*philosopher_routine(void *void_philosopher);
void					philo_sleeps(t_philo *philo);
void					philo_eats(t_philo *philo);
void					smart_sleep(int duration, t_table *table);
void					eat_action_solo(t_table *table, t_philo *philo);
int						check_eat_times(t_table *table, t_philo *philo);
int						check_stop_condition(t_table *table);
=======
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

typedef struct  s_philo
{
    int             id;
    int             eat_count;
    long long int   last_meal;
    pthread_t       thread_id;
    t_init          *holder;
}               t_philo;

int isspace(int c);
int ft_atoi(char *str);
int only_digits(char *str);
int basic_check(int argc, char *input[]);
void load_input(t_init *holder, char *input[]);
>>>>>>> main

#endif
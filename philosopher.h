/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:30:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/15 16:50:20 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647

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

// basic
int						isspace(int c);
int						ft_atoi(char *str);
int						only_digits(char *str);
void					ft_putstr_fd(char *s, int fd);

// load 
void					load_input(t_table *holder, char *input[]);
int						init_table(t_table *table);

// validate
int						validate_input(int argc, char *input[]);

// routine
void					*philosopher_routine(void *arg);
void					philo_sleeps(t_philo *philo);
void					philo_eats(t_philo *philo);
void					eat_action_solo(t_philo *philo);
int						dinner_time(t_table *table);

// time
long long				time_diff(long long past, long long pres);
long long				timestamp(void);

// monitoring
int						check_eat_times(t_table *table, t_philo *philo);
int						check_stop_condition(t_table *table);
void					action_print(t_table *rules, int id, char *string);
void					cleanup_and_exit(t_table *table, t_philo *philos);
void					monitor_philosophers(t_table *table, t_philo *philos);
int						check_all_ate(t_table *table, t_philo *philos);
int						check_death(t_table *table, t_philo *philos);
void					*philosopher_routine(void *void_philosopher);
void					smart_sleep(int duration, t_table *table);

#endif

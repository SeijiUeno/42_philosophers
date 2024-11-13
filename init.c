/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:58:32 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 20:27:10 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philos_setter(t_table *table)
{
	int			i;
	int			guests;
	t_philo		*philo;

	guests = table->number_of_philosophers;
	i = 0;
	while (i < guests)
	{
		philo = &table->philosopher[i];
		philo->id = i;
		philo->eat_count = 0;
		philo->last_meal = 0;
		philo->table = table;
		if (i % 2 == 0)
		{
			philo->left_fork = i;
			philo->right_fork = (i + 1) % guests;
		}
		else
		{
			philo->left_fork = (i + 1) % guests;
			philo->right_fork = i;
		}
		i++;
	}
}

static int	init_table_safeguard(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->writing, NULL) != 0)
	{
		ft_putstr_fd("MUTEX ERROR\n", 2);
		return (1);
	}
	if (pthread_mutex_init(&table->meal_check, NULL) != 0)
	{
		ft_putstr_fd("MUTEX ERROR\n", 2);
		return (1);
	}
	i = table->number_of_philosophers;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_putstr_fd("MUTEX ERROR\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	basic_rules_checker(t_table *table)
{
	if (table->number_of_philosophers > 200)
	{
		ft_putstr_fd("Error: Maximum 200 philosophers allowed.\n", 2);
		return (1);
	}
	return (0);
}

int	init_table(t_table *table)
{
	if (basic_rules_checker(table) || init_table_safeguard(table))
	{
		return (1);
	}
	philos_setter(table);
	return (0);
}

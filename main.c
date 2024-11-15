/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/13 20:25:00 by sueno-te         ###   ########.fr       */
=======
/*   Updated: 2024/11/12 16:10:48 by sueno-te         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

<<<<<<< HEAD
static int	loading(t_table *table, int argc, char *argv[])
=======
static int loading(t_init *holder, int argc, char *argv[])
>>>>>>> main
{
	if (validate_input(argc, argv))
	{
		return (1);
	}
	load_input(table, argv);
	if (init_table(table))
	{
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
<<<<<<< HEAD
	t_table	table;
=======
    t_init  holder;
>>>>>>> main

	if (loading(&table, argc, argv))
	{
		return (1);
	}
	if (dinner_time(&table))
	{
		fprintf(stderr, "Error: Dinner time failed.\n");
		return (1);
	}
	return (0);
}

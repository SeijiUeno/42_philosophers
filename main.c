/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 13:40:42 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int loading(t_table *table, int argc, char *argv[]) {
    if (validate_input(argc, argv)) {
        return (1);
    }
    load_input(table, argv);
    if (init_table(table)) {
        fprintf(stderr, "%s : Initialization ERROR\n", argv[0]);
        return (1);
    }
    return (0); 
}

int main(int argc, char *argv[]) {
    t_table table;

    if (loading(&table, argc, argv)) {
        return (1);
    }

    if (dinner_time(&table))
    {
        fprintf(stderr, "Error: Dinner time failed.\n");
        return (1);
    }

    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 12:23:13 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

static int loading(t_table *table, int argc, char *argv[]) {
    if (validate_input(argc, argv)) {
        fprintf(stderr, "%s : Input ERROR (loading)\n", argv[0]);
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
    int     i;

    if (loading(&table, argc, argv)) {
        return (1);
    }
    
    i = 0;
    while (i < table.number_of_philosophers) {
        if (pthread_create(&table.philosopher[i].thread_id, NULL, philosopher_routine, &table.philosopher[i]) != 0) {
            perror("pthread_create");
            return (1);
        }
        i++;
    }

    i = 0;
    while (i < table.number_of_philosophers) {
        if (pthread_join(table.philosopher[i].thread_id, NULL) != 0) {
            perror("pthread_join");
            return (1);
        }
        i++;
    }

    return (0);
}
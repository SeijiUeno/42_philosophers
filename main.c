/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 10:55:41 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

static int loading(t_table *holder, int argc, char *argv[]) {
    if (validate_input(argc, argv)) {
        fprintf(stderr, "%s : Input ERROR\n", argv[0]);
        return (1);
    }
    load_input(holder, argv);
    if (init_table(holder)) {
        fprintf(stderr, "%s : Initialization ERROR\n", argv[0]);
        return (1);
    }
    return (0); 
}

int main(int argc, char *argv[]) {
    t_table holder;

    if (loading(&holder, argc, argv)) {
        return (1);
    }
    return (0);
}
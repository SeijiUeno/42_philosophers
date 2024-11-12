/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:29 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/12 16:10:48 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

static int loading(t_init *holder, int argc, char *argv[])
{
    if (!basic_check(argc, argv))
    {
        fprintf(stderr, "%s : Basic_Check ERROR\n", argv[0]);
        return (0);
    }
    load_input(holder, argv);
    return(1);
}

int main(int argc, char *argv[])
{
    t_init  holder;

    loading(&holder, argc, argv);
    return (0);
}
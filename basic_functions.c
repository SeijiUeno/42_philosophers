/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:35:54 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/13 11:01:27 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

int isspace(int c) {
    if (c == ' ' || c == '\t' || c == '\n' || 
        c == '\r' || c == '\v' || c == '\f') 
    {
        return (0);
    }
    else 
    {
        return (-1);
    }
}

int ft_atoi(char *str)
{
	unsigned long int	    number;
	int							i;
	
	i = 0;
	while (isspace(str[i]))
        i++;
	number = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
    i = (int)number;
	return (i);
}

int only_digits(char *str)
{
	int	i;

	i = 0;
    if (str[0] == '\0')
        return (-1);
    while (isspace(str[i]))
	{
			i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (0);
}
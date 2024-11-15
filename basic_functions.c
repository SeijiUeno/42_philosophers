/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:35:54 by sueno-te          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/13 20:46:05 by sueno-te         ###   ########.fr       */
=======
/*   Updated: 2024/11/11 16:49:42 by sueno-te         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	ft_atoi(char *str)
{
	unsigned long int	number;
	int					i;

	number = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		if (number > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)number);
}

int	only_digits(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

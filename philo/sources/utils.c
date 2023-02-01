/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:58:51 by francsan          #+#    #+#             */
/*   Updated: 2023/02/01 22:04:51 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	long int	i;
	long int	j;

	i = 1;
	j = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		j = (*str - 48) + (j * 10);
		str++;
		if (i * j > 2147483647)
			error_msg(ERR);
		if (i * j < -2147483648)
			error_msg(ERR);
	}
	return (i * j);
}

void	error_msg(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

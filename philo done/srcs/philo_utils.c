/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:16:17 by timartin          #+#    #+#             */
/*   Updated: 2023/03/29 14:59:24 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&data()->m_check_eat);
	if (philo->eat_lock == 0)
	{
		if (philo->eat_counter == data()->nr_must_eat)
		{
			data()->eat_flag += 1;
			philo->eat_lock = 1;
		}
		if (data()->eat_flag == data()->nr_philo)
		{
			pthread_mutex_unlock(&data()->m_check_eat);
			return (0);
		}
	}
	pthread_mutex_unlock(&data()->m_check_eat);
	return (1);
}

int	check_all(t_philo *philo)
{
	pthread_mutex_lock(&data()->m_dead_philo);
	if (data()->dead_flag == 1 || data()->eat_flag == data()->nr_philo)
	{
		pthread_mutex_unlock(&data()->m_dead_philo);
		return (0);
	}
	if ((get_time(0) - philo->last_eat) > data()->time_die)
	{
		data()->dead_flag = 1;
		printf("%s%lld ms -> Philosopher %d %s\n",
			RED, get_time(data()->start_time), philo->id, DEAD);
		pthread_mutex_unlock(&data()->m_dead_philo);
		return (0);
	}
	if (!check_eat(philo))
	{
		pthread_mutex_unlock(&data()->m_dead_philo);
		return (0);
	}
	pthread_mutex_unlock(&data()->m_dead_philo);
	return (1);
}

long long	get_time(long long t0)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001)) - t0);
}

void	ft_usleep(long long time)
{
	struct timeval	start_time;
	struct timeval	current_time;
	long long	start;
	long long	current;

	gettimeofday(&start_time, NULL);
	start = ((start_time.tv_usec / 1000) + (start_time.tv_sec * 1000));
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = ((current_time.tv_usec / 1000) + (current_time.tv_sec * 1000));
		if (current - start >= time / 1000)
			break ;
		usleep(50);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	return (num *= sign);
}

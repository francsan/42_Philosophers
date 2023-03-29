/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:53 by timartin          #+#    #+#             */
/*   Updated: 2023/01/16 17:56:58 by timartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_info *info, char **av)
{
	int	i;

	data()->nr_philo = ft_atoi(av[1]);
	data()->time_die = ft_atoi(av[2]);
	data()->time_eat = ft_atoi(av[3]);
	data()->time_sleep = ft_atoi(av[4]);
	data()->dead_flag = 0;
	data()->eat_flag = 0;
	if (av[5])
		data()->nr_must_eat = ft_atoi(av[5]);
	else
		data()->nr_must_eat = -1;
	data()->forks = malloc(sizeof(data()->forks) * data()->nr_philo);
	if (!data()->forks)
		p_error(info, "Fork malloc fail\n");
	i = -1;
	while (++i < data()->nr_philo)
		data()->forks[i] = 0;
	init_philo(info);
}

void	init_philo(t_info *info)
{
	int	i;

	info->philo = malloc(sizeof(t_philo) * (data()->nr_philo));
	if (!info->philo)
		p_error(info, "Philo malloc fail\n");
	i = -1;
	while (++i < data()->nr_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].time_die = data()->time_die;
		info->philo[i].eat_counter = 0;
		info->philo[i].eat_lock = 0;
		info->philo[i].last_eat = 0;
		info->philo[i].philo_dead = 0;
		info->philo[i].fork = 0;
		if (i < data()->nr_philo)
		{
			info->philo[i].left = i;
			info->philo[i].right = i + 1;
			if (i == (data()->nr_philo - 1))
				info->philo[i].right = 0;
		}
	}
	init_mutex(info);
}

void	init_mutex(t_info *info)
{
	int	i;

	data()->m_fork = malloc(sizeof(pthread_mutex_t) * data()->nr_philo);
	if (!data()->m_fork)
		p_error(info, "Fork mutex malloc fail\n");
	i = -1;
	while (++i < data()->nr_philo)
		pthread_mutex_init(&data()->m_fork[i], NULL);
	pthread_mutex_init(&data()->m_dead_philo, NULL);
	pthread_mutex_init(&data()->m_check_eat, NULL);
	pthread_mutex_init(&data()->m_counter, NULL);
}

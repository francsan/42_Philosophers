/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:46:09 by francisco         #+#    #+#             */
/*   Updated: 2023/02/27 02:11:15 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long long	get_time(t_rules *rules)
{
	struct timeval	tv;
	long long		sec;
	long long		usec;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec - rules->start_time.tv_sec;
	usec = tv.tv_usec - rules->start_time.tv_usec;
	return ((usec / 1000) + (sec * 1000));
}

long long	time_since_last(t_rules *rules, t_philo *philo)
{
	if (philo->meals != 0)
		return (get_time(rules) - philo->last_meal);
	return (get_time(rules));
}

long long	time_until_death(t_rules *rules, t_philo *philo)
{
	long long	temp;

	temp = time_since_last(rules, philo);
	if (temp > rules->time_die)
		return (0);
	return (rules->time_die - temp);
}

void	release_forks(t_rules *rules, t_philo *philo)
{
	rules->forks_bool[philo->left_fork] = 0;
	rules->forks_bool[philo->right_fork] = 0;
	pthread_mutex_unlock(&rules->forks[philo->left_fork]);
	pthread_mutex_unlock(&rules->forks[philo->right_fork]);
}

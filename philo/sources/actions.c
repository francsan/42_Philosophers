/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:41:10 by francisco         #+#    #+#             */
/*   Updated: 2023/02/27 02:25:18 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	send_to_die(t_rules *rules, t_philo *philo, long long sleep)
{
	usleep(sleep * 1000);
	pthread_mutex_lock(&rules->death_lock);
	if (rules->is_dead)
	{
		pthread_mutex_unlock(&rules->death_lock);
		return ;
	}
	rules->is_dead += 1;
	printf("%lld %d %s\n", get_time(rules), philo->id + 1, "is dead");
	pthread_mutex_unlock(&rules->death_lock);
}

int	printer(t_rules *rules, t_philo *philo, char *message)
{
	pthread_mutex_lock(&rules->death_lock);
	if (rules->is_dead)
	{
		pthread_mutex_unlock(&rules->death_lock);
		return (1);
	}
	printf("%lld %d %s\n", get_time(rules), philo->id + 1, message);
	pthread_mutex_unlock(&rules->death_lock);
	return (0);
}

int	check_meals(t_rules *rules, t_philo *philo)
{
	if (philo->meals == rules->num_meals && rules->is_dead == 0)
		rules->meals_done++;
	if (rules->meals_done == rules->num_philo)
	{
		rules->is_dead += 1;
		printf("%lld All Philosophers have eaten enough meals!\n", get_time(rules));
		return (1);
	}
	return (0);
}

int	take_forks(t_rules *rules, t_philo *philo)
{
	while (rules->forks_bool[philo->right_fork] == 1 || rules->forks_bool[philo->left_fork] == 1)
	{
		if (time_since_last(rules, philo) > rules->time_die)
		{
			send_to_die(rules, philo, time_until_death(rules, philo));
			return (1);
		}
	}
	pthread_mutex_lock(&rules->forks[philo->left_fork]);
	rules->forks_bool[philo->left_fork] = 1;
	if (printer(rules, philo, "has taken a fork"))
	{
		rules->forks_bool[philo->left_fork] = 0;
		pthread_mutex_unlock(&rules->forks[philo->left_fork]);
		return (0);
	}
	if (take_second_fork(rules, philo) == 1)
		return (1);
	return (0);
}

int	take_second_fork(t_rules *rules, t_philo *philo)
{
	while (rules->forks_bool[philo->right_fork] == 1)
	{
		if (time_since_last(rules, philo) > rules->time_die)
		{
			pthread_mutex_unlock(&rules->forks[philo->left_fork]);
			send_to_die(rules, philo, time_until_death(rules, philo));
			return (1);
		}
	}
	pthread_mutex_lock(&rules->forks[philo->right_fork]);
	rules->forks_bool[philo->right_fork] = 1;
	if (printer(rules, philo, "has taken a fork"))
	{
		release_forks(rules, philo);
		return (1);
	}
	if (time_since_last(rules, philo) > rules->time_die)
	{
		release_forks(rules, philo);
		send_to_die(rules, philo, time_until_death(rules, philo));
		return (1);
	}
	return (0);
}

int	start_eating(t_rules *rules, t_philo *philo)
{
	if (printer(rules, philo, "is eating") == 1)
	{
		release_forks(rules, philo);
		return (1);
	}
	if (time_since_last(rules, philo) > rules->time_die || rules->time_eat > rules->time_die)
	{
		release_forks(rules, philo);
		send_to_die(rules, philo, time_until_death(rules, philo));
		return (1);
	}
	philo->meals++;
	check_meals(rules, philo);
	philo->last_meal = get_time(rules);
	usleep(rules->time_eat * 1000);
	return (0);
}

int	start_sleeping(t_rules *rules, t_philo *philo)
{
	if (printer(rules, philo, "is sleeping"))
		return (1);
	release_forks(rules, philo);
	if (time_since_last(rules, philo) + rules->time_sleep > rules->time_die)
	{
		send_to_die(rules, philo, time_until_death(rules, philo));
		return (1);
	}
	usleep(rules->time_sleep * 1000);
	if (printer(rules, philo, "is  thinking"))
		return (1);
	return (0);
}

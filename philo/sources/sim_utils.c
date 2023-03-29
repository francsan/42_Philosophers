/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:05:37 by francisco         #+#    #+#             */
/*   Updated: 2023/03/29 14:30:31 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long long	get_time(t_rules *r)
{
	struct timeval	time;
	long long		usec;
	long long		sec;

	gettimeofday(&time, NULL);
	usec = time.tv_usec - r->start_time.tv_usec;
	sec = time.tv_sec - r->start_time.tv_sec;
	return ((usec / 1000) + (sec * 1000));
}

long long	time_since_last(t_rules *r, t_philo *p)
{
	if (p->num_meals != 0)
		return (get_time(r) - p->last_meal_time);
	return (get_time(r));
}

long long	time_to_die(t_rules *r, t_philo *p)
{
	long long	temp;

	temp = time_since_last(r, p);
	if (temp > r->time_die)
		return (0);
	return (r->time_die - temp);
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

int	printer(t_rules *r, t_philo *p, char *msg)
{
	pthread_mutex_lock(&r->death_lock);
	if (r->death_bool)
	{
		pthread_mutex_unlock(&r->death_lock);
		return (1);
	}
	printf("%lld %d %s\n", get_time(r), p->id + 1, msg);
	pthread_mutex_unlock(&r->death_lock);
	return (0);
}

void	release_forks(t_rules *r, t_philo *p)
{
	r->forks_bool[p->l_fork_id] = 0;
	r->forks_bool[p->r_fork_id] = 0;
	pthread_mutex_unlock(&r->forks[p->l_fork_id]);
	pthread_mutex_unlock(&r->forks[p->r_fork_id]);
}

int	check_meals(t_rules *r, t_philo *p)
{
	if (r->max_meals == -1)
		return (0);
	if (p->num_meals == r->max_meals && r->death_bool == 0)
		r->finished_meals++;
	if (r->finished_meals == r->num_philos)
	{
		r->death_bool = 1;
		printf("%lld %s\n", get_time(r), MEALS);
		return (1);
	}
	return (0);
}

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
	long long		current;

	(void)r;
	gettimeofday(&time, NULL);
	current = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current - r->start_time);
}

void	ft_usleep(long long time)
{
	struct timeval	s_time;
	struct timeval	c_time;
	long long		start;
	long long		current;

	gettimeofday(&s_time, NULL);
	start = ((s_time.tv_usec / 1000) + (s_time.tv_sec * 1000));
	while (1)
	{
		gettimeofday(&c_time, NULL);
		current = ((c_time.tv_usec / 1000) + (c_time.tv_sec * 1000));
		if (current - start >= time)
			break ;
		usleep(50);
	}
}

int	check_eat(t_rules *r, t_philo *p)
{
	pthread_mutex_lock(&r->m_check_eat);
	if (p->eat_lock == 0)
	{
		if (p->eat_counter == r->max_meals)
		{
			r->eat_flag += 1;
			p->eat_lock = 1;
		}
		if (r->eat_flag == r->num_philos)
		{
			pthread_mutex_unlock(&r->m_check_eat);
			return (0);
		}
	}
	pthread_mutex_unlock(&r->m_check_eat);
	return (1);
}

int	check_all(t_rules *r, t_philo *p)
{
	pthread_mutex_lock(&r->m_dead_philo);
	if (r->dead_flag == 1 || r->eat_flag == r->num_philos)
	{
		pthread_mutex_unlock(&r->m_dead_philo);
		return (0);
	}
	if ((get_time(r) - p->last_eat) > r->time_die)
	{
		r->dead_flag = 1;
		printf("%lld ms | %d %s\n", get_time(r), p->id, DEAD);
		pthread_mutex_unlock(&r->m_dead_philo);
		return (0);
	}
	if (!check_eat(r, p))
	{
		pthread_mutex_unlock(&r->m_dead_philo);
		return (0);
	}
	pthread_mutex_unlock(&r->m_dead_philo);
	return (1);
}

void	free_and_destroy(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
		pthread_mutex_destroy(&r->m_fork[i]);
	pthread_mutex_destroy(&r->m_dead_philo);
	pthread_mutex_destroy(&r->m_check_eat);
	pthread_mutex_destroy(&r->m_counter);
	pthread_mutex_destroy(&r->m_increment);
	free(r->m_fork);
	free(r->forks);
	free(r->philos);
}

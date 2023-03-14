/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:29:12 by francisco         #+#    #+#             */
/*   Updated: 2023/03/14 22:59:03 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	send_to_die(t_rules *r, t_philo *p, long long sleep)
{
	usleep(sleep * 1000);
	pthread_mutex_lock(&r->death_lock);
	if (r->death_bool)
	{
		pthread_mutex_unlock(&r->death_lock);
		return ;
	}
	r->death_bool = 1;
	printf("%lld %d %s\n", get_time(r), p->id + 1, DEAD);
	pthread_mutex_unlock(&r->death_lock);
}

int	take_forks(t_rules *r, t_philo *p)
{
	while (pthread_mutex_lock(&r->forks[p->l_fork_id]) != 0)
	{
		if (time_since_last(r, p) > r->time_die)
		{
			send_to_die(r, p, time_to_die(r, p));
			return (1);
		}
	}
	if (printer(r, p, FORK))
	{
		pthread_mutex_unlock(&r->forks[p->l_fork_id]);
		return (0);
	}
	if (take_second_fork(r, p))
		return (1);
	return (0);
}

int	take_second_fork(t_rules *r, t_philo *p)
{
	if (p->r_fork_id == 0 && ((p->id != r->num_philos - 1) || p->id == 0))
	{
		pthread_mutex_unlock(&r->forks[p->l_fork_id]);
		send_to_die(r, p, time_to_die(r, p));
		return (1);
	}
	while (pthread_mutex_lock(&r->forks[p->r_fork_id]) != 0)
	{
		if (time_since_last(r, p) > r->time_die)
		{
			pthread_mutex_unlock(&r->forks[p->l_fork_id]);
			send_to_die(r, p, time_to_die(r, p));
			return (1);
		}
	}
	if (printer(r, p, FORK))
	{
		release_forks(r, p);
		return (1);
	}
	return (0);
}

int	start_eating(t_rules *r, t_philo *p)
{
	if (printer(r, p, EAT))
	{
		release_forks(r, p);
		return (1);
	}
	if (time_since_last(r, p) > r->time_die || r->time_eat > r->time_die)
	{
		release_forks(r, p);
		send_to_die(r, p, time_to_die(r, p));
		return (1);
	}
	p->num_meals++;
	check_meals(r, p);
	p->last_meal_time = get_time(r);
	usleep(r->time_eat * 1000);
	return (0);
}

int	start_sleeping(t_rules *r, t_philo *p)
{
	if (printer(r, p, SLEEP))
	{
		release_forks(r, p);
		return (1);
	}
	release_forks(r, p);
	if (time_since_last(r, p) + r->time_sleep > r->time_die)
	{
		send_to_die(r, p, time_to_die(r, p));
		return (1);
	}
	usleep(r->time_sleep * 1000);
	if (printer(r, p, THINK))
		return (1);
	return (0);
}

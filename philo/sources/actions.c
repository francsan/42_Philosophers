/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:29:12 by francisco         #+#    #+#             */
/*   Updated: 2023/03/15 18:01:32 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	check_fork(t_rules *r, t_philo *p, int pos)
{
	pthread_mutex_lock(&r->m_fork[pos]);
	if (r->forks[pos] == 0)
	{
		r->forks[pos] = 1;
		p->fork += 1;
		if (check_all(r, p))
			printf("%lld ms | %d %s\n", get_time(r), p->id, FORK);
	}
	pthread_mutex_unlock(&r->m_fork[pos]);
}

void	philo_eat(t_rules *r, t_philo *p)
{
	while (p->fork != 2 && check_all(r, p))
	{
		check_fork(r, p, p->left);
		check_fork(r, p, p->right);
	}
	if (check_all(r, p))
	{
		p->last_eat = get_time(r);
		if (check_all(r, p))
			printf("%lld ms | %d %s\n", get_time(r), p->id, EAT);
		p->eat_counter += 1;
		check_all(r, p);
		ft_usleep(r->time_eat);
		pthread_mutex_lock(&r->m_fork[p->left]);
		r->forks[p->left] = 0;
		pthread_mutex_unlock(&r->m_fork[p->left]);
		pthread_mutex_lock(&r->m_fork[p->right]);
		r->forks[p->right] = 0;
		pthread_mutex_unlock(&r->m_fork[p->right]);
		p->fork = 0;
		check_all(r, p);
	}
}

void	philo_sleep(t_rules *r, t_philo *p)
{
	pthread_mutex_lock(&r->m_check_eat);
	if (r->dead_flag == 0 && r->eat_flag != r->num_philos)
	{
		pthread_mutex_unlock(&r->m_check_eat);
		printf("%lld ms | %d %s\n", get_time(r), p->id, SLEEP);
		ft_usleep(r->time_sleep);
	}
	else
		pthread_mutex_unlock(&r->m_check_eat);
}

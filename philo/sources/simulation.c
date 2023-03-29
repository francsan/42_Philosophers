/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:59:32 by francisco         #+#    #+#             */
/*   Updated: 2023/03/29 14:32:55 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_one(t_rules *r, t_philo *p)
{
	printf("%lld ms | %d %s\n", get_time(r), p->id, FORK);
	ft_usleep(r->time_die);
	printf("%lld ms | %d %s\n", get_time(r), p->id, DEAD);
	pthread_mutex_lock(&r->m_dead_philo);
	r->dead_flag = 1;
	pthread_mutex_unlock(&r->m_dead_philo);
}

void	*simulation(void *arg)
{
	t_rules		*r;
	t_philo		*p;
	static int	i = 0;

	r = (t_rules *)arg;
	pthread_mutex_lock(&r->m_increment);
	p = &r->philos[i++];
	pthread_mutex_unlock(&r->m_increment);
	if (p->id % 2 == 0)
		ft_usleep(15);
	while (check_all(r, p))
	{
		if (r->num_philos == 1)
			philo_one(r, p);
		else
		{
			if (check_all(r, p))
				philo_eat(r, p);
			if (check_all(r, p))
				philo_sleep(r, p);
			if (check_all(r, p))
				printf("%lld ms | %d %s\n", get_time(r), p->id, THINK);
		}
	}
	return (NULL);
}

void	run_simulation(t_rules *r)
{
	struct timeval	st;
	int				i;

	if (r->max_meals == 0)
		return ;
	gettimeofday(&st, NULL);
	r->start_time = (st.tv_sec * 1000) + (st.tv_usec / 1000);
	i = -1;
	while (++i < r->num_philos)
	{
		r->philos[i].last_eat = r->start_time;
		if (pthread_create(&r->philos[i].philo_thread, NULL, &simulation, r))
			return ;
	}
	i = -1;
	while (++i < r->num_philos)
		pthread_join(r->philos[i].philo_thread, NULL);
}

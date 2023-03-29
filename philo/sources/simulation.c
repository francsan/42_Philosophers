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

void	*simulation(void *arg)
{
	t_rules		*r;
	t_philo		*p;
	static int	philo = 0;

	r = (t_rules *)arg;
	// pthread_mutex_lock(&r->increment_lock);
	p = &r->philos[philo++];
	if (p->id % 2 == 0)
		ft_usleep(15000);
	// pthread_mutex_unlock(&r->increment_lock);
	while (1 && r->finished_meals != r->max_meals)
	{
		if (take_forks(r, p))
			break ;
		if (start_eating(r, p))
			break ;
		if (start_sleeping(r, p))
			break ;
	}
	return (0);
}

void	start_threads(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
		pthread_create(&r->threads[i], NULL, simulation, (void *)r);
	i = -1;
	while (++i < r->num_philos)
		pthread_join(r->threads[i], NULL);
}

void	destroy_threads(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
		pthread_mutex_destroy(&r->forks[i]);
	pthread_mutex_destroy(&r->death_lock);
	pthread_mutex_destroy(&r->increment_lock);
}

void	run_simulation(t_rules *r)
{
	r->sim_start = get_time(r);
	r->finished_meals = 0;
	r->death_bool = 0;
	start_threads(r);
	destroy_threads(r);
}

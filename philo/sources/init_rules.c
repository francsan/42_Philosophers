/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:16:50 by francisco         #+#    #+#             */
/*   Updated: 2023/03/29 15:40:22 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (2);
	return (0);
}

int	init_alloc(t_rules *r)
{
	r->forks = ft_calloc(r->num_philos, sizeof(int));
	if (!r->forks)
		return (1);
	r->philos = ft_calloc(r->num_philos, sizeof(t_philo));
	if (!r->philos)
		return (2);
	r->m_fork = ft_calloc(r->num_philos, sizeof(pthread_mutex_t));
	if (!r->m_fork)
		return (3);
	return (0);
}

void	init_philos(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
	{
		r->philos[i].id = i + 1;
		r->philos[i].time_die = r->time_die;
		r->philos[i].eat_counter = 0;
		r->philos[i].eat_lock = 0;
		r->philos[i].last_eat = 0;
		r->philos[i].philo_dead = 0;
		r->philos[i].fork = 0;
		if (i < r->num_philos)
		{
			r->philos[i].left = i;
			r->philos[i].right = (i + 1) % r->num_philos;
		}
	}
}

int	init_mutexes(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
	{
		if (pthread_mutex_init(&r->m_fork[i], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&r->m_dead_philo, NULL) != 0)
		return (2);
	if (pthread_mutex_init(&r->m_check_eat, NULL) != 0)
		return (3);
	if (pthread_mutex_init(&r->m_counter, NULL) != 0)
		return (4);
	if (pthread_mutex_init(&r->m_increment, NULL) != 0)
		return (5);
	return (0);
}

int	init_rules(t_rules *r, char **argv)
{
	r->num_philos = ft_atoi(argv[1]);
	r->time_die = ft_atoi(argv[2]);
	r->time_eat = ft_atoi(argv[3]);
	r->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		r->max_meals = ft_atoi(argv[5]);
	else
		r->max_meals = -1;
	if (init_alloc(r))
		return (1);
	init_philos(r);
	init_mutexes(r);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:16:50 by francisco         #+#    #+#             */
/*   Updated: 2023/03/15 02:46:53 by francisco        ###   ########.fr       */
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
	r->forks_bool = ft_calloc(r->num_philos, sizeof(int));
	if (!r->forks_bool)
		return (1);
	r->forks = ft_calloc(r->num_philos, sizeof(pthread_mutex_t));
	if (!r->forks)
		return (2);
	r->threads = ft_calloc(r->num_philos, sizeof(pthread_t));
	if (!r->threads)
		return (3);
	r->philos = ft_calloc(r->num_philos, sizeof(t_philo));
	if (!r->philos)
		return (4);
	return (0);
}

int	init_mutexes(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
	{
		if (pthread_mutex_init(&r->forks[i], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&r->death_lock, NULL) != 0)
		return (2);
	if (pthread_mutex_init(&r->increment_lock, NULL) != 0)
		return (3);
	return (0);
}

void	init_philos(t_rules *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philos)
	{
		r->philos[i].id = i;
		r->philos[i].l_fork_id = i;
		r->philos[i].r_fork_id = (i + 1) % r->num_philos;
		r->philos[i].num_meals = 0;
		r->philos[i].last_meal_time = 0;
	}
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
	gettimeofday(&r->start_time, NULL);
	if (init_alloc(r))
		return (1);
	if (init_mutexes(r))
		return (2);
	init_philos(r);
	return (0);
}

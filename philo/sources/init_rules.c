/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:19:10 by francisco         #+#    #+#             */
/*   Updated: 2023/03/07 16:21:56 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	init_aloc(t_rules *rules)
{
	rules->forks_bool = ft_calloc(rules->num_philo, sizeof(int)); // fork[i] = 0 if free to use OR fork[i] = 1 if being used
	if (!rules->forks_bool)
		return (1);
	rules->forks = ft_calloc(rules->num_philo, sizeof(pthread_mutex_t)); // fork mutexes
	if (!rules->forks)
		return (2);
	rules->philos = ft_calloc(rules->num_philo, sizeof(t_philo)); // philosophers structs info (id, forks id, meals eaten, time of last meal)
	if (!rules->philos)
		return (3);
	rules->threads = ft_calloc(rules->num_philo, sizeof(pthread_t)); // threads
	if (!rules->threads)
		return (4);
	return (0);
}

int	init_mut(t_rules *rules)
{
	int	i;

	i = rules->num_philo;
	while (--i >= 0)
		if (pthread_mutex_init(&rules->forks[i], NULL)) // initializes forks mutexes
			return (1);
	if (pthread_mutex_init(&rules->death_lock, NULL)) // initializes death_lock mutex
		return (2);
	if (pthread_mutex_init(&rules->increment_lock, NULL)) // initializes increment_lock mutex
		return (3);
	return (0);
}

void	init_philo(t_rules *rules) // sets philosophers struct info (id, fork ids, meals eaten, last meal time)
{
	int	i;

	i = rules->num_philo;
	while (--i >= 0)
	{
		rules->philos[i].id = i;
		rules->philos[i].left_fork = rules->philos[i].id;
		rules->philos[i].right_fork = (rules->philos[i].id + 1) % rules->num_philo;
		rules->philos[i].meals = 0;
		rules->philos[i].last_meal = 0;
	}
}

// gets rules from arguments, checks if they're possible to run
// gets start time

int	init_rules(char **argv, t_rules *rules)
{
	rules->num_philo = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->num_meals = ft_atoi(argv[5]);
	else
		rules->num_meals = -1;
	if (rules->num_philo < 1 || rules->time_die < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0)
		return (1);
	gettimeofday(&rules->start_time, NULL);
	if (init_aloc(rules)) // allocates memory for forks, philosophers and their threads
		return (2);
	if (init_mut(rules)) // initializes mutexes
		return (3);
	init_philo(rules); // initializes philosophers structs and fills their info
	return (0);
}

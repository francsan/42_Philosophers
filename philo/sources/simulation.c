/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:37:21 by francisco         #+#    #+#             */
/*   Updated: 2023/03/07 16:26:17 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*simulation(void	*arg)
{
	t_rules		*rules;
	t_philo		*philo;
	static int	counter = 0;

	rules = (t_rules *)arg;
	pthread_mutex_lock(&rules->increment_lock);
	philo = &rules->philos[counter++];
	if (philo->id % 2 == 0)
		usleep(5 * 1000);
	pthread_mutex_unlock(&rules->increment_lock);
	while (1 && rules->num_meals != 0)
	{
		if (take_forks(rules, philo))
			break ;
		if (start_eating(rules, philo))
			break ;
		if (start_sleeping(rules, philo))
			break ;
	}
	return (0);
}

void	init_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		pthread_create(&(rules->threads[i]), NULL, simulation, (void *)rules);
		i++;
	}
}

void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		pthread_join(rules->threads[i], NULL);
		i++;
	}
}

void	destroy_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->death_lock);
	pthread_mutex_destroy(&rules->increment_lock);
}

int	start_simulation(t_rules *rules)
{
	rules->sim_start = get_time(rules);
	init_threads(rules);
	join_threads(rules);
	destroy_threads(rules);
	return (0);
}

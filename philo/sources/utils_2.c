/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:35:13 by francsan          #+#    #+#             */
/*   Updated: 2023/03/07 16:42:31 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	printer(t_rules *rules, t_philo *philo, char *message)
{
	pthread_mutex_lock(&rules->death_lock);
	if (rules->is_dead)
	{
		pthread_mutex_unlock(&rules->death_lock);
		return (1);
	}
	printf("%lld %d %s\n", get_time(rules), philo->id + 1, message);
	pthread_mutex_unlock(&rules->death_lock);
	return (0);
}

int	check_meals(t_rules *rules, t_philo *philo)
{
	if (philo->meals == rules->num_meals && rules->is_dead == 0)
		rules->meals_done++;
	if (rules->meals_done == rules->num_philo)
	{
		rules->is_dead += 1;
		printf("%lld %s", get_time(rules), MEALS);
		return (1);
	}
	return (0);
}

void	free_all(t_rules *rules)
{
	free(rules->forks);
	free(rules->forks_bool);
	free(rules->threads);
	free(rules->philos);
	free(rules);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	check_all_digit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	return (0);
}

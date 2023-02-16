/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/02/08 19:14:46 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*myThread(void *vargp)
{
	t_data	**d;
	int		i;
	int		j;

	d = (t_data **)vargp;
	printf("actual philo = %d\n", (*d)->philo_actual);
	i = (*d)->philo_actual;
	j = (*d)->philo_actual + 1;
	if (j >= (*d)->philo_num)
		j = 0;
	if ((*d)->forks[i] == 0 && (*d)->forks[j] == 0)
	{
		(*d)->forks[i] = 1;
		(*d)->forks[j] = 1;
		pthread_mutex_lock(&(*d)->fork[i]);
		pthread_mutex_lock(&(*d)->fork[j]);
		usleep((*d)->eat_time);
		(*d)->forks[i] = 0;
		(*d)->forks[j] = 0;
		pthread_mutex_unlock(&(*d)->fork[i]);
		pthread_mutex_unlock(&(*d)->fork[j]);
		printf("Philosopher %d has eaten.\n", (*d)->philo_actual);
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	t_data	*d;
	int		i;

	if (argc < 5 || argc > 6)
		return (0);
	d = malloc(sizeof(t_data));
	d->philo_num = ft_atoi(argv[1]);
	d->die_time = ft_atoi(argv[2]);
	d->eat_time = ft_atoi(argv[3]);
	d->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		d->eat_times = ft_atoi(argv[5]);
	else
		d->eat_times = 0;
	d->time = 0;

	d->philo = ft_calloc(d->philo_num, sizeof(pthread_t));
	d->fork = ft_calloc(d->philo_num, sizeof(pthread_mutex_t));
	d->forks = ft_calloc(d->philo_num, sizeof(int));

	i = -1;
	while (++i < d->philo_num)
	{
		d->philo_actual = i;
		if (pthread_create(&d->philo[i], NULL, myThread, &d) != 0)
			return (1);
	}

	i = -1;
	while (++i < d->philo_num)
	{
		if (pthread_mutex_init(&d->fork[i], NULL) != 0)
			return (3);
	}

	i = -1;
	while (++i < d->philo_num)
	{
		if (pthread_join(d->philo[i], NULL) != 0)
			return (2);
	}

	free(d->philo);
	free(d->fork);
	free(d->forks);
	free(d);
	return (0);
}

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
	struct timeval	time;

	(void)vargp;
	if (gettimeofday(&time, NULL) != 0)
		exit(1);
	
	printf("%ld:%ld | Hello from thread\n", time.tv_sec, time.tv_usec);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*d;
	int		i;

	if (argc < 5)
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

	i = -1;
	while (++i < d->philo_num)
	{
		if (pthread_create(&d->philo[i], NULL, myThread, NULL) != 0)
			return (1);
		sleep(2);
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
		if (i == d->philo_num - 1)
		{
			if (pthread_mutex_lock(&d->fork[i]) == 0 && pthread_mutex_lock(&d->fork[i - i]) == 0)
				if (pthread_join(d->philo[i], NULL) != 0)
					return (2);
			pthread_mutex_unlock(&d->fork[i - i]);
		}
		else if (pthread_mutex_lock(&d->fork[i]) == 0 && pthread_mutex_lock(&d->fork[i + 1]) == 0)
			if (pthread_join(d->philo[i], NULL) != 0)
				return (2);
		pthread_mutex_unlock(&d->fork[i]);
		pthread_mutex_unlock(&d->fork[i + 1]);
		printf("Thread %i has finished execution.\n", i);
	}
	free(d);
	return (0);
}

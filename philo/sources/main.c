/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/02/01 22:56:42 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*myThread(void *vargp)
{
	t_philo	**philo;

	philo = (t_philo **)vargp;
	printf("%d\n", (*philo)->n);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*d;

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

	d->tail = malloc(sizeof(t_philo));
	d->tail->n = 1;
	pthread_create(&d->tail->t_id, NULL, myThread, (void *)&d->tail);
	pthread_join(d->tail->t_id, NULL);
	free(d);
	return (0);
}

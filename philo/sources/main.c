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
	t_philo	**philo;

	philo = (t_philo **)vargp;
	printf("%d\n", (*philo)->n);
	usleep(50);
	return (NULL);
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

	i = 1;
	while (i <= d->philo_num)
	{
		if (i == 1)
			init_list(&d->tail, &d->head, i);
		else
			add_node_head(&d->head, i);
		i++;
	}

	t_philo	*curr;
	curr = d->tail;
	while (curr != NULL)
	{
		pthread_create(&curr->t_id, NULL, myThread, (void *)&curr);
		curr = curr->next;
	}

	curr = d->tail;
	while (curr != NULL)
	{
		pthread_join(curr->t_id, NULL);
		curr = curr->next;
	}

	free(d);
	return (0);
}

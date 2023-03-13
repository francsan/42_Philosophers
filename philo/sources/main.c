/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/03/10 22:59:19 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	free_alloc(t_rules *r)
{
	free(r->philos);
	free(r->threads);
	free(r->forks);
	free(r->forks_bool);
	free(r);
}

int	main(int argc, char **argv)
{
	t_rules	*r;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argv))
			return (1);
	}
	else
		return (2);
	r = ft_calloc(1, sizeof(t_rules));
	if (!r)
		return (3);
	if (init_rules(r, argv))
		return (4);
	run_simulation(r);
	free_alloc(r);
	return (0);
}

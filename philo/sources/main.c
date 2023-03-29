/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/03/29 15:40:56 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

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
	if (r->eat_flag == r->num_philos)
		printf("%lld ms | %s\n", get_time(r), MEALS);
	free_and_destroy(r);
	return (0);
}

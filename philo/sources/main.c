/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/02/28 15:52:58 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	free_all(t_rules *rules) // free allocated memory
{
	free(rules->forks);
	free(rules->forks_bool);
	free(rules->threads);
	free(rules->philos);
	free(rules);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc != 5 && argc != 6) // missing arg checker
		return (0);
	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (1);
	if (init_rules(argv, rules)) // defines rules
		return (2);
	start_simulation(rules); // runs simulation
	free_all(rules); // free allocated memory
	return (0);
}

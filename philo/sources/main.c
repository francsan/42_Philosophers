/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/03/07 16:41:21 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc != 5 && argc != 6)
		return (0);
	if (check_all_digit(argv))
		return (1);
	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (2);
	if (init_rules(argv, rules))
		return (3);
	start_simulation(rules);
	free_all(rules);
	return (0);
}

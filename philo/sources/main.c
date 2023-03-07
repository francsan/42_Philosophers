/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:12:52 by francsan          #+#    #+#             */
/*   Updated: 2023/03/07 16:16:12 by francsan         ###   ########.fr       */
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

	i = -1;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc != 5 && argc != 6)
		return (0);
	if (check_all_digit(&argv[1]))
		return (1);
	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (2);
	if (init_rules(argv, rules)) // defines rules
		return (3);
	start_simulation(rules); // runs simulation
	free_all(rules); // free allocated memory
	return (0);
}

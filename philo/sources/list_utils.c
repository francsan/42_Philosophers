/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:56:56 by francisco         #+#    #+#             */
/*   Updated: 2023/02/08 18:30:14 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	free_list(t_philo **tail, t_philo **head)
{
	t_philo	*curr;

	if (*tail == NULL)
		return ;
	curr = *tail;
	while (curr->next != NULL)
	{
		curr = curr->next;
		free(curr->prev);
	}
	free(curr);
	*tail = NULL;
	*head = NULL;
}

void	remove_node(t_philo *philo)
{
	if (philo->prev != NULL)
		philo->prev->next = philo->next;
	if (philo->next != NULL)
		philo->next->prev = philo->prev;
	free(philo);
}

void	add_node_tail(t_philo **tail, int n)
{
	t_philo	*new_philo;

	new_philo = ft_calloc(sizeof(t_philo), 1);
	if (!new_philo)
		error_msg(ERR);
	new_philo->n = n;
	new_philo->next = *tail;
	new_philo->prev = NULL;
	(*tail)->prev = new_philo;
	*tail = new_philo;
}

void	add_node_head(t_philo **head, int n)
{
	t_philo	*new_philo;

	new_philo = ft_calloc(sizeof(t_philo), 1);
	if (!new_philo)
		error_msg(ERR);
	new_philo->n = n;
	new_philo->next = NULL;
	new_philo->prev = *head;
	(*head)->next = new_philo;
	*head = new_philo;
}

void	init_list(t_philo **tail, t_philo **head, int n)
{
	t_philo	*new_philo;

	new_philo = ft_calloc(sizeof(t_philo), 1);
	if (!new_philo)
		error_msg(ERR);
	new_philo->n = n;
	new_philo->prev = NULL;
	new_philo->next = NULL;
	*tail = new_philo;
	*head = new_philo;
}
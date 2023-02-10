/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:26:32 by francsan          #+#    #+#             */
/*   Updated: 2023/02/08 18:30:36 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* libraries */

// memset
# include <string.h>
// printf
# include <stdio.h>
// malloc and free
# include <stdlib.h>
// write and usleep
# include <unistd.h>
// gettimeofday 
# include <sys/time.h>
// pthread_create, pthread_detach, pthread_join,
// pthread_mutex_init, pthread_mutex_destroy,
// pthread_mutex_lock, pthread_mutex_unlock
# include <pthread.h>

/* errors */

# define ERR "Error\n"

/* structs */

typedef struct t_philo {
	int				n;
	pthread_t		t_id;
	struct t_philo	*next;
	struct t_philo	*prev;
}	t_philo;

typedef struct t_data {
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_times;
	int				time;
	struct t_philo	*head;
	struct t_philo	*tail;
}	t_data;

/* sources */

// list_utils.c
void	free_list(t_philo **tail, t_philo **head);
void	remove_node(t_philo *node);
void	add_node_tail(t_philo **tail, int n);
void	add_node_head(t_philo **head, int n);
void	init_list(t_philo **tail, t_philo **head, int n);

// utils.c
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	error_msg(char *error);

#endif
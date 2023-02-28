/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:26:32 by francsan          #+#    #+#             */
/*   Updated: 2023/02/27 02:25:50 by francisco        ###   ########.fr       */
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
	int			id;
	int			right_fork;
	int			left_fork;
	int			meals;
	long		last_meal;
	pthread_t	thread_id;
}	t_philo;

typedef struct t_rules {
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	int				is_dead;
	int				meals_done;
	int				*forks_bool;
	pthread_t		*threads;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	increment_lock;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	struct t_philo			*philos;
	long long		sim_start;
}	t_rules;


/* sources */

// actions.c
void		send_to_die(t_rules *rules, t_philo *philo, long long sleep);
int			printer(t_rules *rules, t_philo *philo, char *message);
int			check_meals(t_rules *rules, t_philo *philo);
int			take_forks(t_rules *rules, t_philo *philo);
int			take_second_fork(t_rules *rules, t_philo *philo);
int			start_eating(t_rules *rules, t_philo *philo);
int			start_sleeping(t_rules *rules, t_philo *philo);

// functions.c
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		error_msg(char *error);

// init_rules.c
int			init_aloc(t_rules *rules);
int			init_mut(t_rules *rules);
void		init_philo(t_rules *rules);
int			init_rules(char **argv, t_rules *rules);

// simulation.c
void		*simulation(void	*arg);
void		init_threads(t_rules *rules);
void		join_threads(t_rules *rules);
void		destroy_threads(t_rules *rules);
int			start_simulation(t_rules *rules);

// utils.c
long long	get_time(t_rules *rules);
long long	time_since_last(t_rules *rules, t_philo *philo);
long long	time_until_death(t_rules *rules, t_philo *philo);
void		release_forks(t_rules *rules, t_philo *philo);

#endif
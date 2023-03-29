/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:26:32 by francsan          #+#    #+#             */
/*   Updated: 2023/03/29 15:42:01 by francisco        ###   ########.fr       */
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

/* messages */
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define MEALS "All Philosophers have finished eating"
# define DEAD "is dead"

/* structs */

typedef struct t_philo
{
	pthread_t	philo_thread;
	long long	last_eat;
	int			id;
	int			eat_counter;
	int			eat_lock;
	int			time_die;
	int			fork;
	int			right;
	int			left;
	int			philo_dead;
}	t_philo;

typedef struct t_rules
{
	long long		start_time;
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_flag;
	int				dead_flag;
	int				print_flag;
	int				max_meals;
	int				*forks;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_dead_philo;
	pthread_mutex_t	m_check_eat;
	pthread_mutex_t	m_counter;
	t_philo			*philos;
}	t_rules;

/* sources */

// actions.c
void		send_to_die(t_rules *r, t_philo *p);
int			take_forks(t_rules *r, t_philo *p);
int			take_second_fork(t_rules *r, t_philo *p);
int			start_eating(t_rules *r, t_philo *p);
int			start_sleeping(t_rules *r, t_philo *p);

// init_rules.c
int			check_args(char **argv);
int			init_alloc(t_rules *r);
void		init_philos(t_rules *r);
int			init_mutexes(t_rules *r);
int			init_rules(t_rules *r, char **argv);

// sim_utils.c
long long	get_time(t_rules *r);
long long	time_since_last(t_rules *r, t_philo *p);
long long	time_to_die(t_rules *r, t_philo *p);
void		ft_usleep(long long time);
int			printer(t_rules *r, t_philo *p, char *msg);
void		release_forks(t_rules *r, t_philo *p);
int			check_meals(t_rules *r, t_philo *p);

// simulation.c
void		*simulation(void *arg);
void		start_threads(t_rules *r);
void		destroy_threads(t_rules *r);
void		run_simulation(t_rules *r);

// utils.c
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);

#endif
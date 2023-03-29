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

/* colors */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define CYAN "\033[96m"
# define DEFAULT "\033[0m"

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
	pthread_mutex_t	m_increment;
	t_philo			*philos;
}	t_rules;

/* sources */

// actions.c
void		check_fork(t_rules *r, t_philo *p, int pos);
void		philo_eat(t_rules *r, t_philo *philo);
void		philo_sleep(t_rules *r, t_philo *philo);

// init_rules.c
int			check_args(char **argv);
int			init_alloc(t_rules *r);
void		init_philos(t_rules *r);
int			init_mutexes(t_rules *r);
int			init_rules(t_rules *r, char **argv);

// sim_utils.c
long long	get_time(t_rules *r);
void		ft_usleep(long long time);
int			check_eat(t_rules *r, t_philo *p);
int			check_all(t_rules *r, t_philo *p);
void		free_and_destroy(t_rules *r);

// simulation.c
void		philo_one(t_rules *r, t_philo *p);
void		*simulation(void *arg);
void		run_simulation(t_rules *r);

// utils.c
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);

#endif
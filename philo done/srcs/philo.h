/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:22:39 by timartin          #+#    #+#             */
/*   Updated: 2023/03/29 14:58:34 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define CYAN "\033[96m"
# define DEFAULT "\033[0m"

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define MEALS "All Philosophers have finished eating"
# define DEAD "is dead"

typedef struct s_p_data
{
	long long		start_time;
	int				nr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_flag;
	int				dead_flag;
	int				print_flag;
	int				nr_must_eat;
	int				*forks;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_dead_philo;
	pthread_mutex_t	m_check_eat;
	pthread_mutex_t	m_counter;
}	t_p_data;

typedef struct s_philo
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

typedef struct s_info
{
	t_philo	*philo;
}	t_info;

// philo.c
t_p_data	*data(void);
void		p_error(t_info *info, char *msg);
void		check_args(char **av);

// init.c
void		init_data(t_info *info, char **av);
void		init_philo(t_info *info);
void		init_mutex(t_info *info);

// handle_threads.c
void		start_threads(t_info *info);
void		*routine(void *args);
void		philo_one(t_philo *philo);
void		free_and_destroy(t_info *info);

// handle_actions.c
void		check_fork(t_philo *philo, pthread_mutex_t *lock, int pos);
void		eat(t_philo *philo);
void		zzz_sleep(t_philo *philo);

// philo_utils.c
int			check_all(t_philo *philo);
int			check_eat(t_philo *philo);
int			ft_atoi(const char *str);
long long	get_time(long long t0);
void		ft_usleep(long long time);

#endif

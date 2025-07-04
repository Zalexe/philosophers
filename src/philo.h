/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:27:14 by cmarrued          #+#    #+#             */
/*   Updated: 2025/04/16 16:27:16 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define PHILO_MAX_COUNT 200

typedef pthread_t		t_id;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write_lock;
	t_mutex	*meal_lock;
}	t_mutexes;

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_philo
{
	int			id;
	t_times		times;
	t_mutexes	mutexes;
	int			must_eat;
	t_id		thread_id;
	int			meals_eaten;
	int			philo_count;
}	t_philo;

typedef struct s_simulation
{
	t_mutex	*forks;
	t_philo	*philos;
	t_mutex	meal_lock;
	t_mutex	write_lock;
}	t_simulation;

void	init_philos(t_simulation *sims,
			t_philo *philos, t_mutex *forks, char **argv);
void	init_forks(t_simulation *sim, t_mutex *forks, int count);
void	init_simulation(t_simulation *sim,
			t_philo *philos, t_mutex *forks);

bool	is_all_eat(t_philo *philos);
void	*observer(void *ptr);
void	philo_routine(t_philo *philo);
void	*start_simulation(void *ptr);
void	ft_simulation(t_simulation *sim, int count);

void	error_message(char *text, int er_nmbr);
void	destroy_all(t_simulation *sim, char *str, int count, int er_nmbr);
void	print_action(t_philo *philo, char *action);
size_t	get_current_time(void);
void	ft_usleep(size_t mls);
long	ft_atol(const char *str);
#endif

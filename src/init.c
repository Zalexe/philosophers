/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:29:44 by cmarrued          #+#    #+#             */
/*   Updated: 2025/04/16 16:29:51 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	init_philos(t_simulation *sim,
			t_philo *philos, t_mutex *forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].times.die = ft_atol(argv[2]);
		philos[i].times.eat = ft_atol(argv[3]);
		philos[i].times.sleep = ft_atol(argv[4]);
		philos[i].times.last_meal = get_current_time();
		philos[i].times.born_time = get_current_time();
		philos[i].must_eat = -1;
		if (argv[5])
			philos[i].must_eat = ft_atol(argv[5]);
		philos[i].meals_eaten = 0;
		philos[i].philo_count = ft_atol(argv[1]);
		philos[i].mutexes.left_fork = &forks[i];
		if (i == 0)
			philos[i].mutexes.right_fork = &forks[philos[i].philo_count - 1];
		else
			philos[i].mutexes.right_fork = &forks[i - 1];
		philos[i].mutexes.write_lock = &sim->write_lock;
		philos[i].mutexes.meal_lock = &sim->meal_lock;
	}
}

void	init_forks(t_simulation *sim, t_mutex *forks, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			destroy_all(sim, "Mutex Init ERROR\n", i, 1);
	}
}

void	init_simulation(t_simulation *sim,
			t_philo *philos, t_mutex *forks)
{
	sim->forks = forks;
	sim->philos = philos;
	if (pthread_mutex_init(&sim->write_lock, NULL) != 0
		|| pthread_mutex_init(&sim->meal_lock, NULL) != 0)
		destroy_all(sim, "Mutex Init ERROR\n", -1, 1);
}

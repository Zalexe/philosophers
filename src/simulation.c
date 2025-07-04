/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:38:32 by cmarrued          #+#    #+#             */
/*   Updated: 2025/04/16 16:38:34 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	is_all_eat(t_philo *philos)
{
	int		finished;
	int		i;

	i = -1;
	finished = 0;
	if (philos[0].must_eat == -1)
		return (false);
	while (++i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eat)
			++finished;
		pthread_mutex_unlock(philos->mutexes.meal_lock);
	}
	if (finished == philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.write_lock);
		return (true);
	}
	return (false);
}

void	*observer(void *ptr)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)ptr;
	while (true)
	{
		i = -1;
		while (++i < philos[0].philo_count)
		{
			pthread_mutex_lock(philos->mutexes.meal_lock);
			if (get_current_time() - philos[i].times.last_meal
				> philos[i].times.die)
			{
				pthread_mutex_unlock(philos->mutexes.meal_lock);
				print_action(&philos[i], " died");
				pthread_mutex_lock(philos->mutexes.write_lock);
				return (NULL);
			}
			pthread_mutex_unlock(philos->mutexes.meal_lock);
		}
		if (is_all_eat(philos))
			return (NULL);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->mutexes.left_fork;
	second = philo->mutexes.right_fork;
	if (philo->mutexes.right_fork < philo->mutexes.left_fork)
	{
		first = philo->mutexes.right_fork;
		second = philo->mutexes.left_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->meals_eaten += 1;
	philo->times.last_meal = get_current_time();
	print_action(philo, " is eating");
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	ft_usleep(philo->times.eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	print_action(philo, " is sleeping");
	ft_usleep(philo->times.sleep + (philo->philo_count % 2));
	print_action(philo, " is thinking");
}

void	*start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (true)
		philo_routine(philo);
	return (NULL);
}

void	ft_simulation(t_simulation *sim, int count)
{
	t_id	observer_id;
	int		i;

	i = -1;
	if (pthread_create(&observer_id, NULL, &observer, sim->philos) != 0)
		destroy_all(sim, "Thread Creation ERROR\n", count, 1);
	while (++i < count)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL,
				start_simulation, &sim->philos[i]) != 0)
			destroy_all(sim, "Thread Creation ERROR\n", count, 1);
	}
	i = -1;
	if (pthread_join(observer_id, NULL) != 0)
		destroy_all(sim, "Thread Join ERROR\n", count, 1);
	while (++i < count)
	{
		if (pthread_detach(sim->philos[i].thread_id) != 0)
			destroy_all(sim, "Thread Detach ERROR\n", count, 1);
	}
}

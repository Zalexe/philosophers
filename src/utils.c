/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:38:52 by cmarrued          #+#    #+#             */
/*   Updated: 2025/04/16 16:38:54 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

size_t	get_current_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_message("gettimeofday() ERROR\n", 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < mls)
		usleep(500);
}

void	error_message(char *text, int er_nmbr)
{
	size_t	i;

	i = 0;
	while (text[i] != '\0')
		i++;
	if (text)
		write(2, text, i + 1);
	exit(er_nmbr);
}

void	destroy_all(t_simulation *sim, char *str, int count, int er_nmbr)
{
	while (--count >= 0)
		pthread_mutex_destroy(&sim->forks[count]);
	pthread_mutex_destroy(&sim->write_lock);
	pthread_mutex_destroy(&sim->meal_lock);
	error_message(str, er_nmbr);
}

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	pthread_mutex_lock(philo->mutexes.write_lock);
	time = get_current_time() - philo->times.born_time;
	printf("[%ld] %d%s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->mutexes.write_lock);
}

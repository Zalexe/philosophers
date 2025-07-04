/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:27:44 by cmarrued          #+#    #+#             */
/*   Updated: 2025/04/16 16:27:46 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	check_args(int argc, char **argv)
{
	int		i;
	long	num;

	i = 0;
	if (argc < 5 || argc > 6)
		error_message("Argument Count ERROR\n", 1);
	while (++i < argc)
	{
		num = ft_atol(argv[i]);
		if (i == 1 && (num < 1 || num > PHILO_MAX_COUNT))
			error_message("Argument ERROR\n", 1);
		else if (i == 5 && (num < 0 || num > INT_MAX))
			error_message("Argument ERROR\n", 1);
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			error_message("Argument ERROR\n", 1);
	}
}

int	main(int argc, char **argv)
{
	t_philo			philos[PHILO_MAX_COUNT];
	t_mutex			forks[PHILO_MAX_COUNT];
	t_simulation	sim;

	check_args(argc, argv);
	init_simulation(&sim, philos, forks);
	init_forks(&sim, forks, ft_atol(argv[1]));
	init_philos(&sim, philos, forks, argv);
	ft_simulation(&sim, philos[0].philo_count);
	return (0);
}

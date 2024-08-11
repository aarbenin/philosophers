/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:36:57 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:37:04 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_simulation(t_simulation *sim)
{
	sim->is_sim_over = false;
	sim->philosophers = malloc(sim->num_philo * sizeof(t_philosopher));
	if (!sim->philosophers)
		return (FAILURE);
	sim->forks = malloc(sim->num_philo * sizeof(pthread_mutex_t));
	if (!sim->forks)
	{
		free(sim->philosophers);
		return (FAILURE);
	}
	sim->threads = malloc(sim->num_philo * sizeof(pthread_t));
	if (!sim->threads)
	{
		free(sim->forks);
		free(sim->philosophers);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	init_philo_data(t_simulation *sim)
{
	int	i;

	pthread_mutex_init(&sim->sim_end_mutex, NULL);
	pthread_mutex_init(&sim->log_mutex, NULL);
	i = 0;
	while (i < sim->num_philo)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < sim->num_philo)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].r_fork = &sim->forks[i];
		sim->philosophers[i].l_fork = &sim->forks[(i + 1) % sim->num_philo];
		sim->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&sim->philosophers[i].last_meal_mutex, NULL);
		pthread_mutex_init(&sim->philosophers[i].meals_eaten_mutex, NULL);
		sim->philosophers[i].sim_data = sim;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				result;

	result = process_args(&sim, argc, argv);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	if (sim.eat_goal == 0)
		return (EXIT_SUCCESS);
	result = init_simulation(&sim);
	if (result == FAILURE)
	{
		report_error(MEMORY);
		return (EXIT_FAILURE);
	}
	init_philo_data(&sim);
	result = run_simulation(&sim);
	if (result == FAILURE)
	{
		report_error(THREAD_FAILURE);
		cleanup_simulation(&sim);
		return (EXIT_FAILURE);
	}
	cleanup_simulation(&sim);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:37:26 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:37:32 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_over(t_simulation *sim)
{
	pthread_mutex_lock(&sim->sim_end_mutex);
	if (sim->is_sim_over)
	{
		pthread_mutex_unlock(&sim->sim_end_mutex);
		return (true);
	}
	pthread_mutex_unlock(&sim->sim_end_mutex);
	return (false);
}

void	end_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->sim_end_mutex);
	if (!sim->is_sim_over)
	{
		sim->is_sim_over = true;
		pthread_mutex_unlock(&sim->sim_end_mutex);
		return ;
	}
	pthread_mutex_unlock(&sim->sim_end_mutex);
}

static bool	init_philo_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		sim->philosophers[i].last_meal = sim->start_time;
		if (pthread_create(&sim->threads[i], NULL, &philosopher_routine,
				&sim->philosophers[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static bool	start_trackers(t_simulation *sim)
{
	if (pthread_create(&sim->death_tracker, NULL, &death_tracker, sim))
		return (FAILURE);
	if (sim->eat_goal > 0 && sim->num_philo > 1)
	{
		if (pthread_create(&sim->eat_goal_tracker, NULL, &eat_goal_tracker,
				sim))
			return (FAILURE);
	}
	return (SUCCESS);
}

bool	run_simulation(t_simulation *sim)
{
	sim->start_time = get_time(0);
	if (init_philo_threads(sim) == FAILURE)
		return (FAILURE);
	if (start_trackers(sim) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

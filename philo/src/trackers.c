/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:39:38 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:39:44 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long long	last_meal_time(t_philosopher *philo)
{
	unsigned long long	time;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (time);
}

static bool	check_philo_death(t_philosopher *philo, t_simulation *sim)
{
	unsigned long long	time_since_last_meal;
	unsigned long long	time_to_die;

	time_since_last_meal = get_time(last_meal_time(philo));
	time_to_die = (unsigned long long)sim->time_to_die;
	if (time_since_last_meal > time_to_die)
	{
		pthread_mutex_lock(&sim->log_mutex);
		printf("%llu %d died\n", get_time(sim->start_time), philo->id);
		end_simulation(sim);
		pthread_mutex_unlock(&sim->log_mutex);
		return (true);
	}
	return (false);
}

void	*death_tracker(void *arg)
{
	t_simulation	*sim;
	int				i;
	bool			philosopher_died;

	sim = (t_simulation *)arg;
	while (!is_simulation_over(sim))
	{
		i = 0;
		while (i < sim->num_philo)
		{
			philosopher_died = check_philo_death(&sim->philosophers[i], sim);
			if (philosopher_died)
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

static bool	all_goals_met(t_simulation *sim)
{
	int	i;
	int	meal_count;

	i = 0;
	while (i < sim->num_philo)
	{
		meal_count = current_meal_count(&sim->philosophers[i]);
		if (meal_count < sim->eat_goal)
			return (false);
		i++;
	}
	return (true);
}

void	*eat_goal_tracker(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (!is_simulation_over(sim))
	{
		if (all_goals_met(sim))
		{
			end_simulation(sim);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

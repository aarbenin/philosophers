/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:37:12 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:37:17 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philosopher *philo)
{
	if (is_simulation_over(philo->sim_data))
		return ;
	take_forks(philo);
	if (is_simulation_over(philo->sim_data))
	{
		release_forks(philo);
		return ;
	}
	log_philo_action(philo, "is eating");
	update_last_meal_time(philo);
	wait_ms(philo->sim_data->time_to_eat, philo->sim_data);
	release_forks(philo);
}

static void	philo_sleep(t_philosopher *philo)
{
	if (is_simulation_over(philo->sim_data))
		return ;
	log_philo_action(philo, "is sleeping");
	add_meal_count(philo);
	wait_ms(philo->sim_data->time_to_sleep, philo->sim_data);
}

static void	philo_think(t_philosopher *philo)
{
	int	think_time;

	if (is_simulation_over(philo->sim_data))
		return ;
	log_philo_action(philo, "is thinking");
	if ((philo->sim_data->num_philo % 2) != 0)
	{
		think_time = philo->sim_data->time_to_eat * 2
			- philo->sim_data->time_to_sleep;
		wait_ms(think_time, philo->sim_data);
	}
}

static void	*single_philosopher(t_philosopher *philo)
{
	while (!is_simulation_over(philo->sim_data))
	{
		pthread_mutex_lock(philo->r_fork);
		if (is_simulation_over(philo->sim_data))
		{
			pthread_mutex_unlock(philo->r_fork);
			return (NULL);
		}
		log_philo_action(philo, "has taken a fork");
		usleep(10);
		pthread_mutex_unlock(philo->r_fork);
		return (NULL);
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->sim_data->num_philo == 1)
		return (single_philosopher(philo));
	if (philo->id % 2 == 0)
		usleep(50);
	while (!is_simulation_over(philo->sim_data))
	{
		philo_eat(philo);
		if (is_simulation_over(philo->sim_data))
			break ;
		philo_sleep(philo);
		if (is_simulation_over(philo->sim_data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}


#include "philo.h"

static void	philo_eat(t_philosopher *philo)
{
	take_forks(philo);
	log_philo_action(philo, "is eating");
	if (update_last_meal_time(philo) && is_simulation_over(philo->sim_data))
	{
		release_forks(philo);
		return ;
	}
	sleep_ms(philo->sim_data->time_to_eat);
	release_forks(philo);
}

static void	philo_sleep(t_philosopher *philo)
{
	log_philo_action(philo, "is sleeping");
	if (add_meal_count(philo) && is_simulation_over(philo->sim_data))
		return ;
	sleep_ms(philo->sim_data->time_to_sleep);
}

static void	philo_think(t_philosopher *philo)
{
	int	think_time;

	log_philo_action(philo, "is thinking");
	if ((philo->sim_data->num_philo % 2) != 0
		&& !is_simulation_over(philo->sim_data))
	{
		think_time = philo->sim_data->time_to_eat * 2
			- philo->sim_data->time_to_sleep;
		sleep_ms(think_time);
	}
}

static void	*single_philosopher(t_philosopher *philo)
{
	while (!is_simulation_over(philo->sim_data))
	{
		pthread_mutex_lock(philo->r_fork);
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
	while (!is_simulation_over(philo->sim_data)
		&& (philo->sim_data->eat_goal < 0
			|| current_meal_count(philo) < philo->sim_data->eat_goal))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

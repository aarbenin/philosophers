#include "philo.h"

static u_int64_t	last_meal_time(t_philosopher *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (time);
}

static bool	check_philo_death(t_philosopher *philo, t_simulation *sim)
{
	u_int64_t	time_since_last_meal;
	u_int64_t	time_to_die;

	time_since_last_meal = get_time(last_meal_time(philo));
	time_to_die = (u_int64_t)sim->time_to_die;
	if (time_since_last_meal > time_to_die)
	{
		log_philo_action(philo, "died");
		end_simulation(sim);
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
		usleep(1000);
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
	t_simulation *sim;

	sim = (t_simulation *)arg;
	while (!is_simulation_over(sim))
	{
		if (all_goals_met(sim))
			return (end_simulation(sim), NULL);
		usleep(1000);
	}
	return (NULL);
}
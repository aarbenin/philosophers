
#include "philo.h"

void	log_philo_action(t_philosopher *philo, const char *action)
{
	u_int64_t	action_time;

	action_time = get_time(philo->sim_data->start_time);
	if (!is_simulation_over(philo->sim_data))
	{
		pthread_mutex_lock(&philo->sim_data->log_mutex);
		printf("%llu %d %s\n", action_time, philo->id, action);
		pthread_mutex_unlock(&philo->sim_data->log_mutex);
	}
}

bool	update_last_meal_time(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (philo->last_meal != get_time(0))
	{
		philo->last_meal = get_time(0);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (SUCCESS);
}

bool	add_meal_count(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	if (philo->meals_eaten >= 0)
	{
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	return (SUCCESS);
}

int	current_meal_count(t_philosopher *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->meals_eaten_mutex);
	if (philo->meals_eaten >= 0)
	{
		eat_count = philo->meals_eaten;
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		return (eat_count);
	}
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	return (0);
}

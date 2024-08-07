#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		log_philo_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		log_philo_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		log_philo_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		log_philo_action(philo, "has taken a fork");
	}
}

void	release_forks(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

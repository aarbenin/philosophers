#include "philo.h"

static void	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		pthread_join(sim->threads[i], NULL);
		i++;
	}
}

static void	destroy_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philosophers[i].meals_eaten_mutex);
		pthread_mutex_destroy(&sim->philosophers[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->sim_end_mutex);
	pthread_mutex_destroy(&sim->log_mutex);
}

static void	free_sim_memory(t_simulation *sim)
{
	free(sim->threads);
	free(sim->forks);
	free(sim->philosophers);
}

void	cleanup_simulation(t_simulation *sim)
{
	pthread_join(sim->death_tracker, NULL);
	if (sim->eat_goal > 0 && sim->num_philo > 1)
		pthread_join(sim->eat_goal_tracker, NULL);
	join_threads(sim);
	destroy_mutexes(sim);
	free_sim_memory(sim);
}


#include "philo.h"

// arguments.c
static bool	validate_args_count(int arg_count)
{
	if (arg_count < 5)
		return (report_error(NOT_ENOUGH_ARGS), FAILURE);
	if (arg_count > 6)
		return (report_error(ERR_TOO_MANY_ARGS), FAILURE);
	return (SUCCESS);
}

static bool	init_params_base(t_simulation *sim, char **args)
{
	sim->num_philo = ft_atoi(args[1]);
	if (sim->num_philo < 1)
		return (report_error(INVALID_PHILO), FAILURE);
	sim->time_to_die = ft_atoi(args[2]);
	if (sim->time_to_die < 1)
		return (report_error(INVALID_TIME_TO_DIE), FAILURE);
	sim->time_to_eat = ft_atoi(args[3]);
	if (sim->time_to_eat < 1)
		return (report_error(INVALID_TIME_TO_EAT), FAILURE);
	sim->time_to_sleep = ft_atoi(args[4]);
	if (sim->time_to_sleep < 1)
		return (report_error(INVALID_TIME_TO_SLEEP), FAILURE);
	return (SUCCESS);
}

static bool	init_params_opt(t_simulation *sim, int arg_count, char **args)
{
	sim->eat_goal = -1;
	if (arg_count == 6)
	{
		sim->eat_goal = ft_atoi(args[5]);
		if (sim->eat_goal < 0)
			return (report_error(INVALID_EAT_GOAL), FAILURE);
	}
	return (SUCCESS);
}

static bool	process_args(t_simulation *sim, int arg_count, char **args)
{
	if (validate_args_count(arg_count) == FAILURE)
		return (FAILURE);
	if (init_params_base(sim, args) == FAILURE)
		return (FAILURE);
	if (init_params_opt(sim, arg_count, args) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

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

static void	init_philosophers(t_simulation *sim)
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

// cleanup_simulation.c
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

static void	cleanup_simulation(t_simulation *sim)
{
	pthread_join(sim->death_tracker, NULL);
	if (sim->eat_goal > 0 && sim->num_philo > 1)
		pthread_join(sim->eat_goal_tracker, NULL);
	join_threads(sim);
	destroy_mutexes(sim);
	free_sim_memory(sim);
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
	init_philosophers(&sim);
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

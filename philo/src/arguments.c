#include "philo.h"

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

bool	process_args(t_simulation *sim, int arg_count, char **args)
{
	if (validate_args_count(arg_count) == FAILURE)
		return (FAILURE);
	if (init_params_base(sim, args) == FAILURE)
		return (FAILURE);
	if (init_params_opt(sim, arg_count, args) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
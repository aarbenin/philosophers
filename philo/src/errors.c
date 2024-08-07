#include "philo.h"

static void	display_err_details(const char *err_details,
		const char *expected_val)
{
	if (err_details && ft_strlen(err_details) > 0)
		printf("\nOops! Something went wrong:\n%s", err_details);
	if (expected_val && ft_strlen(expected_val) > 0)
		printf(" Required: %s", expected_val);
	printf("\n\n");
}

static void	handle_arg_error(char error_type)
{
	const char	*arg_description = "";

	if (error_type == INVALID_PHILO)
		arg_description = " (number of philosophers at the table)";
	else if (error_type == INVALID_TIME_TO_DIE)
		arg_description = " (time until a philosopher starves)";
	else if (error_type == INVALID_TIME_TO_EAT)
		arg_description = " (time needed for a philosopher to eat)";
	else if (error_type == INVALID_TIME_TO_SLEEP)
		arg_description = " (time a philosopher spends sleeping)";
	else if (error_type == INVALID_EAT_GOAL)
	{
		arg_description = " (times each philosopher needs to eat)";
		display_err_details("", "Please enter a positive number");
		return ;
	}
	printf("\nLooks like argument %d is not quite right%s", error_type - 2,
		arg_description);
	display_err_details("", "Please enter a positive number");
}

void	report_error(char error_type)
{
	if (error_type >= INVALID_PHILO && error_type <= INVALID_EAT_GOAL)
		handle_arg_error(error_type);
	else if (error_type == NOT_ENOUGH_ARGS)
		display_err_details("Some arguments are missing!",
			"Need 4 or 5 inputs.");
	else if (error_type == MEMORY)
		display_err_details("Couldn't allocate memory.", "");
	else if (error_type == ERR_TOO_MANY_ARGS)
		display_err_details("Too many arguments given!",
			"Only 4 or 5 allowed.");
	else if (error_type == THREAD_FAILURE)
		display_err_details("Thread creation failed!", "");
}

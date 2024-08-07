#include "philo.h"

u_int64_t	get_time(u_int64_t base_time)
{
	struct timeval	now;
	u_int64_t		current_time_ms;

	gettimeofday(&now, NULL);
	current_time_ms = (now.tv_sec * 1000ULL) + (now.tv_usec / 1000);
	return (current_time_ms - base_time);
}

void	sleep_ms(u_int64_t delay_ms)
{
	u_int64_t start_time;
	u_int64_t current_time;

	start_time = get_time(0);
	current_time = start_time;
	while ((current_time - start_time) < delay_ms)
	{
		usleep(500);
		current_time = get_time(0);
	}
}
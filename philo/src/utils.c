
#include "philo.h"

// time.c
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
	u_int64_t	start_time;
	u_int64_t	current_time;

	start_time = get_time(0);
	current_time = start_time;
	while ((current_time - start_time) < delay_ms)
	{
		usleep(500);
		current_time = get_time(0);
	}
}
// utils.c

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

size_t	ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
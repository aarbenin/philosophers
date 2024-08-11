/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:39:11 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:39:21 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(unsigned long long base_time)
{
	struct timeval		now;
	unsigned long long	current_time_ms;

	gettimeofday(&now, NULL);
	current_time_ms = (now.tv_sec * 1000ULL) + (now.tv_usec / 1000);
	return (current_time_ms - base_time);
}

void	wait_ms(unsigned long long delay_ms, t_simulation *sim)
{
	unsigned long long	start_time;
	unsigned long long	current_time;

	start_time = get_time(0);
	current_time = start_time;
	while ((current_time - start_time) < delay_ms)
	{
		if (is_simulation_over(sim))
		{
			break ;
		}
		usleep(500);
		current_time = get_time(0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:34:49 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:34:59 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libraries.h"

typedef struct s_philosopher
{
	int						id;
	int						meals_eaten;
	unsigned long long		last_meal;
	pthread_mutex_t			meals_eaten_mutex;
	pthread_mutex_t			last_meal_mutex;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
	struct s_simulation		*sim_data;
}							t_philosopher;

typedef struct s_simulation
{
	struct s_philosopher	*philosophers;
	unsigned long long		start_time;
	int						num_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						eat_goal;
	pthread_t				*threads;
	pthread_t				death_tracker;
	pthread_t				eat_goal_tracker;
	pthread_mutex_t			sim_end_mutex;
	pthread_mutex_t			log_mutex;
	pthread_mutex_t			*forks;
	bool					is_sim_over;
}							t_simulation;

enum						e_error_type
{
	NOT_ENOUGH_ARGS,
	ERR_TOO_MANY_ARGS,
	INVALID_PHILO,
	INVALID_TIME_TO_DIE,
	INVALID_TIME_TO_EAT,
	INVALID_TIME_TO_SLEEP,
	INVALID_EAT_GOAL,
	THREAD_FAILURE,
	MEMORY
};

enum						e_result_code
{
	SUCCESS,
	FAILURE
};

enum						e_philosopher_state
{
	MEAL_COUNT_UPDATE,
	LAST_MEAL
};

#endif

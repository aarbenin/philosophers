/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:33:15 by aarbenin          #+#    #+#             */
/*   Updated: 2024/08/11 19:34:41 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"

// simulation.c
bool				run_simulation(t_simulation *data);
bool				is_simulation_over(t_simulation *data);
void				end_simulation(t_simulation *data);

// philo_routine.c
void				*philosopher_routine(void *arg);

// philo_state.c
bool				update_last_meal_time(t_philosopher *philo);
bool				add_meal_count(t_philosopher *philo);
int					current_meal_count(t_philosopher *philo);
void				log_philo_action(t_philosopher *philo, const char *action);

// time.c
unsigned long long	get_time(unsigned long long base_time);
void				wait_ms(unsigned long long delay_ms, t_simulation *sim);

// utils.c
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);

// errors.c
void				report_error(char error_type);

// cleanup.c
void				cleanup_simulation(t_simulation *sim);

// fork_management.c
void				take_forks(t_philosopher *philo);
void				release_forks(t_philosopher *philo);

// trackers.c
void				*death_tracker(void *arg);
void				*eat_goal_tracker(void *arg);

// arguments.c
bool				process_args(t_simulation *sim, int arg_count, char **args);

#endif

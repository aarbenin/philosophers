
#ifndef PHILO_H
# define PHILO_H

# include "structs.h"

// simulation.c
bool		run_simulation(t_simulation *data);

// philo_routine.c
void		*philosopher_routine(void *arg);

// sim_control.c
bool		is_simulation_over(t_simulation *data);
void		end_simulation(t_simulation *data);

// philo_state.c
bool		update_last_meal_time(t_philosopher *philo);
bool		add_meal_count(t_philosopher *philo);
int			current_meal_count(t_philosopher *philo);
void		log_philo_action(t_philosopher *philo, const char *action);

// time.c
u_int64_t	get_time(u_int64_t base_time);
void		sleep_ms(u_int64_t delay_ms);

// utils.c
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *str);

// errors.c
void		report_error(char error_type);

#endif

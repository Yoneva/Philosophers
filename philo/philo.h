/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:33:40 by user              #+#    #+#             */
/*   Updated: 2025/07/28 16:48:40 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	bool			simulation_over;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print;
	long long		start_time;
	int				num_philos;
	pthread_mutex_t	*fork;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_goal;
	pthread_mutex_t	meal_mutex;
	long long		last_meal_time;
	int				meal_eaten;
	int				left_fork;
	int				right_fork;
	t_data			*shared_data;
}	t_philo ;

int			ft_atoi(const char *str);
void		smart_sleep(long duration, t_philo *philo);
bool		check_status(t_philo *philo);
void		ms_sleep(int ms);
void		print(t_philo *philo, char *str);
long long	elapsed_time_ms(t_data *data);
long long	current_time_ms(void);
bool		check_death(void *arg, int n_philos);
void		s_leep(t_philo *philo);
void		eat(t_philo *philo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:33:40 by user              #+#    #+#             */
/*   Updated: 2025/07/30 18:05:13 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				args_nb;
	bool			simulation_over;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print;
	long long		start_time;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_goal;
	pthread_mutex_t	*fork;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	meal_mutex;
	long long		last_meal_time;
	int				meal_eaten;
	int				left_fork;
	int				right_fork;
	t_data			*shared_data;
}	t_philo;

int			ft_atoi(const char *str);
bool		check_if_0(t_data *shared_data, int i);
bool		done_eating(t_philo	*philo);
void		smart_sleep(long duration, t_philo *philo);
int			parse_data(t_data	*shared_data, int n_philo, int ac, char **av);
void		init_philos(t_data *shared_data, t_philo *philo, pthread_t *thread);
bool		check_status(t_philo *philo);
void		clean(t_data *shared_data, t_philo *philo, pthread_t *thread);
void		print(t_philo *philo, char *str);
long long	elapsed_time_ms(t_data *data);
long long	current_time_ms(void);
bool		check_death(t_philo	*philo);
void		s_leep(t_philo *philo);
void		eat(t_philo *philo);
int			valid_nbr(const char *tab);

#endif
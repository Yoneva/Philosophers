/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:39:23 by user              #+#    #+#             */
/*   Updated: 2025/07/17 21:30:17 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(void *arg, int n_philos)
{
	int i;
	t_philo	*philos = (t_philo *)arg;
	t_data *data = philos[0].shared_data;

	i = 0;
	while(i < n_philos)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (current_time_ms() - philos[i].last_meal_time > philos[i].time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			if (!data->simulation_over)
			{
				print(&philos[i], "died");
				data->simulation_over = true;
			}
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (true);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	s_leep(t_philo *philo)
{
	print(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

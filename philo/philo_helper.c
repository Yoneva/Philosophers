/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:39:23 by user              #+#    #+#             */
/*   Updated: 2025/07/28 21:00:42 by amsbai           ###   ########.fr       */
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
			usleep(1000);
			return (false);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (true);
}

void	smart_sleep(long duration, t_philo *philo)
{
	long	start;
	
	start = current_time_ms();
	while (check_status(philo))
	{
		if (current_time_ms() - start >= duration)
			break;
		usleep(1000);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->fork[philo->left_fork]);
	print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->shared_data->fork[philo->right_fork]);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	smart_sleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);	
	pthread_mutex_unlock(&philo->shared_data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->shared_data->fork[philo->right_fork]);
}

void	s_leep(t_philo *philo)
{	
	print(philo, "is sleeping");
	smart_sleep(philo->time_to_sleep, philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:39:23 by user              #+#    #+#             */
/*   Updated: 2025/07/29 21:31:38 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_philo	*philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (current_time_ms() - philo->last_meal_time > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->shared_data->death_mutex);
		if (!philo->shared_data->simulation_over)
		{
			print(philo, "died");
			philo->shared_data->simulation_over = true;
		}
		pthread_mutex_unlock(&philo->shared_data->death_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
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

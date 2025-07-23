/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:52:31 by user              #+#    #+#             */
/*   Updated: 2025/07/17 20:48:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

long long elapsed_time_ms(t_data *data)
{
	return (current_time_ms() - data->start_time);
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared_data->print);
	printf("%lld %d %s\n", elapsed_time_ms(philo->shared_data), philo->id,
		str);
	pthread_mutex_unlock(&philo->shared_data->print);
}

void ms_sleep(int ms)
{
	long long start = current_time_ms();
	while (current_time_ms() - start < ms)
		usleep(500); // sleep in small increments to be more accurate
}

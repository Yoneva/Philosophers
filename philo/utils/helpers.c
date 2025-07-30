/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:52:31 by user              #+#    #+#             */
/*   Updated: 2025/07/30 18:07:03 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared_data->print);
	if (philo->shared_data->simulation_over == false)
		printf("%lld %d %s\n", elapsed_time_ms(philo->shared_data), philo->id,
			str);
	pthread_mutex_unlock(&philo->shared_data->print);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:40:48 by user              #+#    #+#             */
/*   Updated: 2025/07/30 18:04:47 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	done_eating(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->shared_data->num_philos)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meal_eaten < philo[i].shared_data->meals_goal)
		{
			pthread_mutex_unlock(&philo[i].meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&philo->shared_data->death_mutex);
	philo->shared_data->simulation_over = true;
	pthread_mutex_unlock(&philo->shared_data->death_mutex);
	return (true);
}

void	set_forks(pthread_mutex_t *forks, int id)
{
	int	i;

	i = 0;
	while (i < id)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

bool	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->death_mutex);
	if (philo->shared_data->simulation_over)
	{
		pthread_mutex_unlock(&philo->shared_data->death_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->shared_data->death_mutex);
	return (true);
}

int	main(int ac, char **av)
{
	int			n_philos;
	int			i;
	pthread_t	*thread;
	t_philo		*philo;
	t_data		shared_data;

	if (ac != 5 && ac != 6)
		return (0);
	i = 0;
	while (++i < ac)
	{
		if (valid_nbr(av[i]))
			return (printf("Error !! unvalide number\n"));
	}
	n_philos = ft_atoi(av[1]);
	thread = malloc(sizeof (pthread_t) * n_philos);
	philo = malloc(sizeof(t_philo) * n_philos);
	if (!philo || !thread)
		return (free(philo), free(thread), 0);
	i = parse_data(&shared_data, n_philos, ac, av);
	if (i < 0)
		return (check_if_0(&shared_data, i));
	set_forks(shared_data.fork, n_philos);
	init_philos(&shared_data, philo, thread);
	clean(&shared_data, philo, thread);
}

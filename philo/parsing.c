/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:45:44 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/30 18:04:16 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_data(t_data *shared_data, int n_philo, int ac, char **av)
{
	shared_data->args_nb = ac;
	if (ac == 6)
	{
		shared_data->meals_goal = ft_atoi(av[5]);
		if (shared_data->meals_goal == 0)
			return (-2);
	}
	shared_data->time_to_die = ft_atoi(av[2]);
	shared_data->time_to_eat = ft_atoi(av[3]);
	shared_data->time_to_sleep = ft_atoi(av[4]);
	shared_data->num_philos = n_philo;
	if (n_philo == 0 || shared_data->time_to_die == 0
		|| shared_data->time_to_sleep == 0 || shared_data->time_to_eat == 0)
		return (-1);
	shared_data->simulation_over = false;
	shared_data->start_time = current_time_ms();
	pthread_mutex_init(&shared_data->death_mutex, NULL);
	pthread_mutex_init(&shared_data->print, NULL);
	shared_data->fork = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!shared_data->fork)
		return (-1);
	return (1);
}

void	clean(t_data *shared_data, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < shared_data->num_philos)
	{
		pthread_join(thread[i], NULL);
		pthread_mutex_destroy(&shared_data->fork[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&shared_data->death_mutex);
	pthread_mutex_destroy(&shared_data->print);
	free(shared_data->fork);
	free(philo);
	free (thread);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->shared_data->num_philos == 1)
	{
		print(philo, "has taken a fork");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		s_leep(philo);
	while (check_status(philo))
	{
		print(philo, "is thinking");
		eat(philo);
		s_leep(philo);
	}
	return (NULL);
}

void	init_philos(t_data *shared_data, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < shared_data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].meal_eaten = 0;
		philo[i].last_meal_time = shared_data->start_time;
		philo[i].shared_data = shared_data;
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % shared_data->num_philos;
		pthread_create(&thread[i], NULL, routine, &philo[i]);
	}
	while (1)
	{
		if (!check_death(philo))
			break ;
		if (shared_data->args_nb == 6)
		{
			if (done_eating(philo))
				break ;
		}
		usleep(42);
	}
}

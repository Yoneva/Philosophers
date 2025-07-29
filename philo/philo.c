/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:40:48 by user              #+#    #+#             */
/*   Updated: 2025/07/29 21:31:15 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*philo_action(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

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

int main(int ac, char **av)
{
	int		id;
	int		n;

	if (ac < 5 || ac > 6)
		return (0);
	id = ft_atoi(av[1]);
	pthread_t	*thread;
	t_philo		*philo;
	t_data shared_data;
	shared_data.num_philos = id;
	shared_data.simulation_over = false;
	shared_data.start_time = current_time_ms();
	pthread_mutex_init(&shared_data.death_mutex, NULL);
	pthread_mutex_init(&shared_data.print, NULL);
	shared_data.fork = malloc(sizeof(pthread_mutex_t) * id);
	thread = malloc(sizeof (pthread_t) * id);
	philo = malloc(sizeof(t_philo) * id);
	if (!shared_data.fork || !philo || !thread)
		return 1;
	set_forks(shared_data.fork, id);
	n = 0;
	while (n < id)
	{
		philo[n].id = n + 1;
		philo[n].time_to_die = ft_atoi(av[2]);
		philo[n].time_to_eat = ft_atoi(av[3]);
		philo[n].time_to_sleep = ft_atoi(av[4]);
		philo[n].last_meal_time = shared_data.start_time;
		philo[n].shared_data = &shared_data;
		pthread_mutex_init(&philo[n].meal_mutex, NULL);
		if (ac == 6)
			philo[n].meals_goal = ft_atoi(av[5]);
		philo[n].left_fork = n;
		philo[n].right_fork = (n + 1) % id;
		pthread_create(&thread[n], NULL, philo_action, &philo[n]);
		n++;
	}
	while (1)
	{
		if (!check_death(philo))
			break;
		usleep(42);
	}
	n = 0;
	while(n < id)
	{
		pthread_join(thread[n],NULL);
		pthread_mutex_destroy(&shared_data.fork[n]);
		pthread_mutex_destroy(&philo[n].meal_mutex);
		n++;
	}
	pthread_mutex_destroy(&shared_data.death_mutex);
	pthread_mutex_destroy(&shared_data.print);
	free(shared_data.fork);
	free(philo);
	free (thread);
	return (0);
}

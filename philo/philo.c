/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:40:48 by user              #+#    #+#             */
/*   Updated: 2025/07/29 23:38:53 by amsbai           ###   ########.fr       */
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

int main(int ac, char **av)
{
	int			n_philos;
	int			i;
	pthread_t	*thread;
	t_philo		*philo;
	t_data		shared_data;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while(i < ac)
	{
		if (valid_nbr(av[i]))
			return (printf("Error !! unvalide number\n"));
		i++;
	}
	n_philos = ft_atoi(av[1]);
	thread = malloc(sizeof (pthread_t) * n_philos);
	philo = malloc(sizeof(t_philo) * n_philos);
	if ( !philo || !thread)
		return (free(philo), free(thread), 0);
	parse_data(&shared_data, n_philos, ac);
	set_forks(shared_data.fork, n_philos);
	init_philos(av, &shared_data, philo, thread);
	clean(&shared_data, philo, thread);
}

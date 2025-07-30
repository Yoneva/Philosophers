/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:17:51 by amsbai            #+#    #+#             */
/*   Updated: 2025/07/30 18:07:44 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

int	valid_nbr(const char *tab)
{
	int	i;

	i = 0;
	if (tab[i] == '+' && tab[i + 1] != '\0')
		i++;
	while (tab[i])
	{
		if (!ft_isdigit(tab[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

bool	check_if_0(t_data *shared_data, int i)
{
	if (i == -1)
	{
		if (shared_data->num_philos == 0 || shared_data->time_to_die == 0
			|| shared_data->time_to_sleep == 0 || shared_data->time_to_eat == 0)
		{
			printf("Error !! unvalide numberr\n");
			return (true);
		}
	}
	return (false);
}

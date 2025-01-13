/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:48:03 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 13:27:53 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v' || c == '-');
}

static long	ft_atoi(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i])
		num = num * 10 + (str[i++] - '0');
	return (num);
}

void	philo_init(int argc, char **argv, t_data *data)
{
	long	i;

	data->philo_size = ft_atoi(argv[1]);
	data->forks = data->philo_size;
	data->philo = malloc(sizeof(t_philo) * data->philo_size);
	if (!data->philo)
		return ;
	pthread_mutex_init(&data->mutex, NULL);
	i = 0;
	while (i < data->philo_size)
	{
		data->philo[i].mutex = &data->mutex;
		data->philo[i].forks = &data->forks;
		data->philo[i].my_forks = 0;
		data->philo[i].id = i;
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->philo[i].times_to_eat = ft_atoi(argv[5]);
		else
			data->philo[i].times_to_eat = -1;
		i++;
	}
}

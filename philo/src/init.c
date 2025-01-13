/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:48:03 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 16:27:49 by jopereir         ###   ########.fr       */
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

static void	set_philo(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_size)
	{
		data->philo[i].left_fork = &data->forks[i % data->philo_size];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->philo_size];
		data->philo[i].philo_size = 0;
		data->philo[i].meals_eaten = 0;
		data->philo[i].timestamp = 0;
		data->philo[i].index = i;
		data->philo[i].id = i + 1;
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->philo[i].meals_to_eat = ft_atoi(argv[5]);
		else
			data->philo[i++].meals_to_eat = -1;
	}
}

void	philo_init(int argc, char **argv, t_data *data)
{
	long	i;

	data->philo_size = ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_size);
	data->philo = malloc(sizeof(t_philo) * data->philo_size);
	if (!data->philo || !data->forks)
		return ;
	i = 0;
	while (i < data->philo_size)
		pthread_mutex_init(&data->forks[i++], NULL);
	set_philo(argc, argv, data);
}

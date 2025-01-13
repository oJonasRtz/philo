/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:28:17 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 13:15:55 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_null(t_data *data)
{
	data->philo = NULL;
	data->philo_size = 0;
	data->forks = 0;
}

void	create(int argc, char **argv)
{
	t_data	data;
	int		i;

	set_null(&data);
	philo_init(argc, argv, &data);
	if (!data.philo)
		return (destroy (&data));
	printf("Quantidade de philos: %ld\n", data.philo_size);
	printf("garfos %ld\n", data.forks);
	pthread_mutex_init(&data.mutex, NULL);
	i = 0;
	while (i < data.philo_size)
	{
		data.philo[i].mutex = &data.mutex;
		data.philo[i].forks = &data.forks;
		i++;
	}
	printf("create\n");
	execute(&data);
	destroy(&data);
	return ;
}

void	execute(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_size)
	{
		if (pthread_create(&data->philo[i].t, NULL,
				&rotine, (void *)&data->philo[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < data->philo_size)
		if (pthread_join(data->philo[i++].t, NULL))
			return ;
	return ;
}

void	destroy(t_data *data)
{
	if (data->philo)
		free(data->philo);
	set_null(data);
	pthread_mutex_destroy(&data->mutex);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:34:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 16:48:48 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_time_ms(t_philo *philo)
{
	gettimeofday(&philo->time, NULL);
	return ((philo->time.tv_sec * 1000) + (philo->time.tv_usec / 1000));
}

static void	try_to_get_forks(t_philo *philo)
{
	printf("%ld %d is thinking\n", philo->timestamp, philo->id);
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", philo->timestamp, philo->id);
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", philo->timestamp, philo->id);
	printf("%ld %d is eating\n", philo->timestamp, philo->id);
	philo->meals_eaten++;
	philo->timestamp += get_time_ms(philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("%ld %d is sleeping\n", philo->timestamp, philo->id);
	usleep(philo->time_to_sleep * 1000);
}

void	*rotine(void *arg)
{
	t_philo	*philo;
	int		died;

	philo = (t_philo *)arg;
	died = 0;
	philo->timestamp = 0;
	while (1)
		try_to_get_forks(philo);
	return (NULL);
}

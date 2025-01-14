/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.philosophers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:34:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/14 15:32:44 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_philo *philo)
{
	gettimeofday(&philo->time, NULL);
	return (philo->time.tv_sec * 1000000 + philo->time.tv_usec);
}

static void	try_to_sleep(t_philo *philo)
{
	if (*philo->died_flag)
		return ;
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d is sleeping\n", philo->current_time / 1000, philo->id);
	usleep(philo->time_to_sleep * 1000);
}

static void	try_to_get_forks(t_philo *philo)
{
	if (*philo->died_flag)
		return ;
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d is thinking\n", philo->current_time / 1000, philo->id);
	get_forks_and_eat(philo);
	try_to_sleep(philo);
}

int	died(t_philo *philo)
{
	if (*philo->died_flag)
		return (1);
	pthread_mutex_lock(philo->died);
	philo->current_time = get_time(philo) - philo->timestamp;
	if (philo->current_time - philo->last_meal >= philo->time_to_die)
	{
		philo->current_time = get_time(philo) - philo->timestamp;
		printf("%ld %d died\n", philo->current_time / 1000, philo->id);
		*philo->died_flag = 1;
		pthread_mutex_unlock(philo->died);
		return (1);
	}
	pthread_mutex_unlock(philo->died);
	return (0);
}

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->timestamp = get_time(philo);
	philo->current_time = 0;
	while (1)
	{
		if (!died(philo))
		{
			if (philo->philo_size == 1)
				case_one_philo(philo);
			else
				try_to_get_forks(philo);
		}
		else
			break ;
	}
	return (NULL);
}

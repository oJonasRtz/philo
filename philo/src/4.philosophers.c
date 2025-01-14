/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.philosophers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:34:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/14 11:38:59 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(t_philo *philo)
{
	gettimeofday(&philo->time, NULL);
	return ((philo->time.tv_sec * 1000) + (philo->time.tv_usec / 1000));
}

static void	try_to_sleep(t_philo *philo)
{
	if (*philo->died_flag)
		return ;
	philo->current_time = get_time_ms(philo) - philo->timestamp;
	printf("%ld %d is sleeping\n", philo->current_time, philo->id);
	usleep(philo->time_to_sleep * 1000);
}

static void	try_to_get_forks(t_philo *philo)
{
	philo->current_time = get_time_ms(philo) - philo->timestamp;
	printf("%ld %d is thinking\n", philo->current_time, philo->id);
	if (*philo->died_flag)
		return ;
	get_forks_and_eat(philo);
	if (*philo->died_flag)
		return ;
	try_to_sleep(philo);
	if (*philo->died_flag)
		return ;
}

static int	died(t_philo *philo)
{
	if (*philo->died_flag)
		return (1);
	pthread_mutex_lock(philo->died);
	if (philo->current_time >= philo->time_to_die)
	{
		philo->current_time = get_time_ms(philo) - philo->timestamp;
		printf("%ld %d died\n", philo->current_time, philo->id);
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
	philo->timestamp = get_time_ms(philo);
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

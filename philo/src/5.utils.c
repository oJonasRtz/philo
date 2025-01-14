/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:15:55 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/14 15:40:45 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	is_dead(t_philo *philo)
// {
// 	if (*philo->died_flag)
// 	{
// 	}
// 	return (0);
// }

// int	time_to_do(long activity, long current_time, long time_to_die)
// {
// 	long	output;

// 	output = (activity - (time_to_die - current_time)) * 1000;
// 	if (output < 0)
// 		return (0);
// 	return (output);
// }

static void	unlock_forks(t_philo *philo, int flag)
{
	if (flag)
	{
		if (philo->index == philo->philo_size - 1)
			pthread_mutex_unlock(philo->right_fork);
		else
			pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}

static void	get_forks(t_philo *philo)
{
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (*philo->died_flag)
		return (unlock_forks(philo, 1));
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d has taken a fork\n", philo->current_time / 1000, philo->id);
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (*philo->died_flag)
		return (unlock_forks(philo, 0));
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d has taken a fork\n", philo->current_time / 1000, philo->id);
}

static void	try_to_eat(t_philo *philo)
{
	if (*philo->died_flag)
		return ;
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d is eating\n", philo->current_time / 1000, philo->id);
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
	philo->last_meal = philo->current_time;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	get_forks_and_eat(t_philo *philo)
{
	if (*philo->died_flag)
		return ;
	get_forks(philo);
	try_to_eat(philo);
}

void	case_one_philo(t_philo *philo)
{
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d is thinking\n", philo->current_time / 1000, philo->id);
	usleep((philo->time_to_die - philo->current_time) * 1000);
	pthread_mutex_lock(philo->died);
	*philo->died_flag = 1;
	pthread_mutex_unlock(philo->died);
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d died\n", philo->current_time / 1000, philo->id);
}

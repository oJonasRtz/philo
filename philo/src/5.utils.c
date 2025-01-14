/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:15:55 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/14 11:40:28 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks_and_eat(t_philo *philo)
{
	if (*philo->died_flag)
		return ;
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	philo->current_time = get_time_ms(philo) - philo->timestamp;
	printf("%ld %d has taken a fork\n", philo->current_time, philo->id);
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	philo->current_time = get_time_ms(philo) - philo->timestamp;
	printf("%ld %d has taken a fork\n", philo->current_time, philo->id);
	philo->current_time = get_time_ms(philo) - philo->timestamp;
	printf("%ld %d is eating\n", philo->current_time, philo->id);
	philo->meals_eaten++;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	case_one_philo(t_philo *philo)
{
	philo->current_time = get_time_ms(philo) - philo->timestamp;
	printf("%ld %d is thinking\n", philo->current_time, philo->id);
	usleep((philo->time_to_die - philo->current_time) * 1000);
	pthread_mutex_lock(philo->died);
	*philo->died_flag = 1;
	pthread_mutex_unlock(philo->died);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:15:55 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/17 13:20:24 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (died(philo))
		return ;
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (died(philo))
		return (unlock_forks(philo, 1));
	print_message("has taken a fork", philo);
	if (philo->index == philo->philo_size - 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (died(philo))
		return (unlock_forks(philo, 0));
	print_message("has taken a fork", philo);
}

static void	try_to_eat(t_philo *philo)
{
	if (died(philo))
		return ;
	philo->meals_eaten++;
	philo->last_meal = get_time(philo);
	print_message("is eating", philo);
	if (precise_sleep(philo, philo->time_to_eat))
		return (unlock_forks(philo, 0));
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	get_forks_and_eat(t_philo *philo)
{
	if (ate_all_meals(philo) || died(philo))
		return ;
	get_forks(philo);
	try_to_eat(philo);
}

void	case_one_philo(t_philo *philo)
{
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d is thinking\n", philo->current_time / 1000, philo->id);
	usleep((philo->time_to_die - philo->current_time));
	if (died(philo))
		return ;
}

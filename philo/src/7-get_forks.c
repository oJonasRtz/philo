/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.validation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:23:19 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/16 10:34:53 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int get_fork1(t_philo *philo)
{
	if (died(philo))
		return (1);
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (died(philo))
	{
		if (philo->index % 2 == 0)
			pthread_mutex_unlock(philo->right_fork);
		else
			pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_message("has taken a fork", philo);
	return (0);
}

static int get_fork2(t_philo *philo)
{
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (died(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_message("has taken a fork", philo);
	return (0);
}

int	get_forks(t_philo *philo)
{
	if (get_fork1(philo))
		return (1);
	if (get_fork2(philo))
		return (1);
	return (0);
}

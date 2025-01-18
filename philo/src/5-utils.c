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

static void	try_to_eat(t_philo *philo)
{
	if (died(philo))
		return ;
	philo->meals_eaten++;
	philo->last_meal = get_time(philo);
	print_message("is eating", philo);
	precise_sleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	get_forks_and_eat(t_philo *philo)
{
	if (ate_all_meals(philo) || died(philo) || get_forks(philo))
		return ;
	try_to_eat(philo);
}

void	case_one_philo(t_philo *philo)
{
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d is thinking\n", philo->current_time / 1000, philo->id);
	if (precise_sleep(philo, philo->time_to_die - philo->current_time))
		return ;
}

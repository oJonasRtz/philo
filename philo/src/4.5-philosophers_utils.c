/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.5-philosophers_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:08:38 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/17 11:08:00 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ate_all_meals(t_philo *philo)
{
	return (philo->meals_to_eat == philo->meals_eaten);
}

void	die(t_philo *philo)
{
	print_message("died", philo);
	*philo->died_flag = 1;
}

void	print_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d %s\n", philo->current_time / 1000, philo->id, message);
	pthread_mutex_unlock(philo->print_mutex);
}

void	precise_sleep(t_philo *philo, long time_to_sleep)
{
	long	start;

	start = get_time(philo);
	while ((get_time(philo) - start) < time_to_sleep)
	{
		if (died(philo))
			break ;
		usleep(100);
	}
}

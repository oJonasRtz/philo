/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.5-philosophers_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:08:38 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/16 11:53:28 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ate_all_meals(t_philo *philo)
{
	return (philo->meals_to_eat == philo->meals_eaten);
}

void	die(t_philo *philo)
{
	philo->current_time = get_time(philo) - philo->timestamp;
	printf("%ld %d died\n", philo->current_time / 1000, philo->id);
	*philo->died_flag = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:34:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 13:29:12 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Infos from philo %d\n", philo->id);
	printf("Total forks %ld\n", *philo->forks);
	printf("My forks %d\n", philo->my_forks);
	printf("Time to die %lu\n", philo->time_to_die);
	printf("Time to eat %lu\n", philo->time_to_eat);
	printf("Time to sleep %lu\n", philo->time_to_sleep);
	return (NULL);
}

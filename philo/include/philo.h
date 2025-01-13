/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:22:04 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 16:30:19 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				index;
	int				id;
	int				philo_size;
	pthread_t		t;

	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	long			meals_to_eat;
	long			meals_eaten;
	long			timestamp;
	struct timeval	time;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;

	t_philo			*philo;
	long			philo_size;
}	t_data;

//	events.c
void	create(int argc, char **argv);
void	execute(t_data *data);
void	destroy(t_data *data);

//	init.c
void	philo_init(int argc, char **argv, t_data *data);

//	philosophers.c
void	*rotine(void *arg);

#endif

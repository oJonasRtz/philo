/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:22:04 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/13 13:15:57 by jopereir         ###   ########.fr       */
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
	pthread_mutex_t	*mutex;
	long			*forks;

	int				id;
	int				my_forks;
	pthread_t		t;

	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;

	long			times_to_eat;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	mutex;
	long			forks;

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

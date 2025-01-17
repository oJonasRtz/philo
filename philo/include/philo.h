/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:22:04 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/17 11:08:11 by jopereir         ###   ########.fr       */
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
	pthread_mutex_t	*died;
	pthread_mutex_t	*print_mutex;

	int				*died_flag;

	int				index;
	int				id;
	int				philo_size;
	pthread_t		t;

	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_to_eat;
	long			meals_eaten;
	long			last_meal;

	long			timestamp;
	long			current_time;
	struct timeval	time;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;

	t_philo			*philo;
	long			philo_size;

	int				died_flag;
	pthread_mutex_t	died_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

//	events.c
void	create(int argc, char **argv);
void	execute(t_data *data);
void	destroy(t_data *data);

//	init.c
void	philo_init(int argc, char **argv, t_data *data);

//	philosophers.c
void	*rotine(void *arg);
long	get_time(t_philo *philo);
int		died(t_philo *philo);
//	utils.c
void	get_forks_and_eat(t_philo *philo);
void	case_one_philo(t_philo *philo);
int		time_to_do(long activity, long current_time, long time_to_die);

//	validation.c
int		validation(char **argv);

//	philosophers_utils.c
int		ate_all_meals(t_philo *philo);
void	die(t_philo *philo);
void	print_message(char *message, t_philo *philo);
void	precise_sleep(t_philo *philo, long time_to_sleep);

//	monitor.c
void	create_monitor(t_data *data);
void	*monitor(void *arg);

#endif

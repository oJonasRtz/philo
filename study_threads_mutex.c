/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   study_threads_mutex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:24:55 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/10 13:02:06 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_struct
{
	pthread_mutex_t	mutex;
	int				x;
}	t_struct;

void	*rotine(void *a)
{
	t_struct	*b;
	int			i;

	b = (t_struct *)a;
	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&b->mutex);
		b->x++;
		pthread_mutex_unlock(&b->mutex);
		i++;
	}
	return (NULL);
}

/*
	thread test
*/
int	main(int argc, char **argv)
{
	pthread_t		*t;
	int				n;
	int				i;
	t_struct		a;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	t = malloc(n * sizeof(pthread_t));
	i = 0;
	a.x = 0;
	pthread_mutex_init(&a.mutex, NULL);
	while (i < n)
		if ((pthread_create(&t[i++], NULL, &rotine, (void *)&a)))
			return (1);
	i = 0;
	while (i < n)
		if (pthread_join(t[i++], NULL))
			return (1);
	pthread_mutex_destroy(&a.mutex);
	printf("x: %d\n", a.x);
	free(t);
	return (0);
}

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

static int	isnumber(char c)
{
	return (c >= '0' && c <= '9');
}

static int	isallnumber(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!isnumber(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	isnegative(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++][0] == '-')
			return (1);
	return (0);
}

static int	iszero(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		if (ft_atoi(argv[i++]) == 0)
			return (1);
	return (0);
}

int	validation(char **argv)
{
	if (isnegative(&argv[1]) || isallnumber(&argv[1]) || iszero(&argv[1]))
		return (1);
	return (0);
}

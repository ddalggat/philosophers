/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:17:38 by gjailbir          #+#    #+#             */
/*   Updated: 2021/11/16 23:08:12 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_programm(int i)
{
	if (i == 1)
		printf("\x1B[31m Error: Can't allocate a memory\n\033");
	if (i == 2)
		printf("\x1B[31m Error: Can't get a time\n\033");
	if (i == 3)
		printf("\x1B[31m Error: Invalid arguments\n\033");
	if (i == 4)
		printf("\x1B[31m Error: Can't init a mutex\n\033");
	if (i == 5)
		printf("\x1B[31m Error: Can't lock a fork\n\033");
	if (i == 6)
		printf("\x1B[31m Error: Can't lock a mutex write\n\033");
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	if (s[i] == '-')
		return (0);
	while (s[i])
		if (ft_isdigit(s[i++]) != 1)
			return (0);
	i = 0;
	while (s[i])
	{
		if (n > 2147483647)
			return (0);
		n = (n * 10) + (s[i++] - 48);
	}
	return ((int)n);
}

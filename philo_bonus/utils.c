/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:51:08 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/11/21 01:12:11 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	error_programm(int i)
{
	if (i == 1)
		printf("\x1B[31m Error: Can't allocate a memory\n\033");
	if (i == 2)
		printf("\x1B[31m Error: Can't get a time\n\033");
	if (i == 3)
		printf("\x1B[31m Error: Invalid arguments\n\033");
	if (i == 4)
		printf("\x1B[31m Error: Can't create a semaphore\n\033");
	if (i == 5)
		printf("\x1B[31m Error: Can't create a fork\n\033");
}

int	ft_atoi(char *str)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
		{
			error_programm(3);
			exit(0);
		}
	}
	i = 0;
	while (str[i])
	{
		if (n > __INT_MAX__)
		{
			error_programm(3);
			exit(0);
		}
		n = (n * 10) + (str[i++] - 48);
	}
	return ((int)n);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	free_all(t_all *all)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_close(all->semaphore->forks);
	sem_close(all->semaphore->write_semaphore);
	free(all->pid);
	free(all->params);
	free(all->semaphore);
	free(all->philosophers);
}

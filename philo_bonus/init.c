/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 22:32:21 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/11/21 01:08:49 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_fix(void)
{
	long			ret_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret_time);
}

int	init_params(t_all *all, char **arv, int arc)
{
		all->params = (t_params *)malloc(sizeof(t_params));
	if (!all->params)
	{
		error_programm(1);
		return (0);
	}
	all->params->number_of_philo = ft_atoi(arv[1]);
	all->params->life_time = ft_atoi(arv[2]);
	all->params->eat_time = ft_atoi(arv[3]);
	all->params->sleep_time = ft_atoi(arv[4]);
	if (arc == 5)
		all->params->number_of_meals = 0;
	else if (arc == 6)
	{
		if (ft_atoi(arv[5]) == __INT_MAX__)
		{
			error_programm(3);
			return (0);
		}
		else
			all->params->number_of_meals = ft_atoi(arv[5]);
	}
	all->params->death_flag = 0;
	return (1);
}

int	init_sems(t_all *all)
{
	all->semaphore = (t_semaphs *)malloc(sizeof(t_semaphs));
	if (!all->semaphore)
	{
		error_programm(1);
		return (0);
	}
	sem_unlink("write");
	sem_unlink("checkd");
	all->semaphore->write_semaphore = sem_open("write", O_CREAT, 0644, 1);
	all->semaphore->checkd = sem_open("checkd", O_CREAT, 0644, 1);
	if (all->semaphore->write_semaphore == SEM_FAILED)
	{
		error_programm(4);
		return (0);
	}
	sem_unlink("forks");
	all->semaphore->forks = sem_open("forks", \
	O_CREAT, 0644, all->params->number_of_philo / 2);
	if (all->semaphore->forks == SEM_FAILED)
	{
		error_programm(5);
		return (0);
	}
	return (1);
}

int	init_philos(t_all *all)
{
	long	start_time;

	start_time = time_fix();
	all->philosophers = (t_philos *)malloc(sizeof(t_philos));
	if (!all->philosophers)
	{
		error_programm(1);
		return (0);
	}
	all->pid = (pid_t *)malloc(sizeof(pid_t) \
	* all->params->number_of_philo);
	if (!all->pid)
	{
		error_programm(1);
		return (0);
	}
	all->philosophers->start = start_time;
	all->philosophers->pid = all->pid;
	all->philosophers->params = all->params;
	all->philosophers->semaphore = all->semaphore;
	all->philosophers->last = 0;
	return (1);
}

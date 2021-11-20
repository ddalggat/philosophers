/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:32:31 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/11/21 01:10:03 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_fix(long wait_time)
{
	long	current_time;
	long	period;

	current_time = time_fix();
	period = current_time + wait_time;
	while (period > current_time)
	{
		usleep(1);
		current_time = time_fix();
	}
}

void	processes(t_philos *philo)
{
	int			i;
	pthread_t	death_check_thread;

	i = 0;
	pthread_create(&death_check_thread, NULL, check_death, (void *)philo);
	pthread_detach(death_check_thread);
	while (!philo->params->death_flag)
	{
		philosopher_eats(philo);
		if (philosopher_full(philo, &i))
			exit (0);
		philosopher_sleeps(philo);
		philosopher_thinks(philo);
	}
}

void	wait_loop(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < all->params->number_of_philo)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			j = 0;
			while (j < all->params->number_of_philo)
			{
				kill(all->philosophers->pid[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
}

int	start_philosopher(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->params->number_of_philo)
	{
		all->philosophers->pid[i] = fork();
		if (all->philosophers->pid[i] == 0)
		{
			all->philosophers->philo_id = i + 1;
			processes(all->philosophers);
		}
		else if (all->philosophers->pid[i] == -1)
		{
			error_programm(5);
			return (0);
		}
		i++;
	}
	wait_loop(all);
	return (1);
}

int	main(int arc, char **arv)
{
	t_all	all;

	if (arc < 5 || arc > 6)
	{
		error_programm(3);
		return (0);
	}
	if (!init_params(&all, arv, arc) || !init_sems(&all) || !init_philos(&all) \
		|| !start_philosopher(&all))
		return (0);
	all.params->death_flag = 1;
	free_all(&all);
	return (0);
}

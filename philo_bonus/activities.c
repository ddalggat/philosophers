/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:35:32 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/11/21 01:12:46 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_full(t_philos *philo, int *i)
{
	if (philo->params->number_of_meals > 0)
	{
		(*i)++;
		if (*i == philo->params->number_of_meals)
		{
			sem_wait(philo->semaphore->write_semaphore);
			printf("\x1B[92mtime (%lu) ms - philo (%d) is full\033[0m🤙\n", \
				time_fix() - philo->start, philo->philo_id);
			sem_post(philo->semaphore->write_semaphore);
			exit (1);
		}
	}
	return (0);
}

void	philosopher_thinks(t_philos *philo)
{
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->params->death_flag == 0)
		printf("\x1B[94mtime (%lu) ms - philo (%d)\x1B[93m is thinking\033[0m🧠\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
}

void	philosopher_sleeps(t_philos *philo)
{
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->params->death_flag == 0)
		printf("\x1B[94mtime (%lu) ms - philo (%d)\x1B[93m is sleeping\033[0m🛏\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
	sleep_fix(philo->params->sleep_time);
}

void	philosopher_eats(t_philos *philo)
{
	sem_wait(philo->semaphore->forks);
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->params->death_flag == 0)
		printf("\x1B[94mtime (%lu) ms - philo (%d)\x1B[93m is taking forks🍴\n\033", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->params->death_flag == 0)
		printf("\x1B[94mtime (%lu) ms - philo (%d)\x1B[93m is eating\033[0m🍕\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
	philo->last = time_fix() - philo->start;
	sleep_fix(philo->params->eat_time);
	sem_post(philo->semaphore->forks);
}

void	*check_death(void *philosopher)
{
	t_philos	*philo;

	philo = (t_philos *)philosopher;
	while (!philo->params->death_flag)
	{
		sem_wait(philo->semaphore->checkd);
		if (time_fix() - philo->start - philo->last \
		> philo->params->life_time)
		{
			sem_wait(philo->semaphore->write_semaphore);
			printf("\x1B[91mtime (%lu) - Philo (%d) is dead\n\033", \
			time_fix() - philo->start, philo->philo_id);
			philo->params->death_flag = 1;
			exit (0);
		}
		sem_post(philo->semaphore->checkd);
	}
	return (NULL);
}

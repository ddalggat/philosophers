/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:17:12 by gjailbir          #+#    #+#             */
/*   Updated: 2021/11/21 00:58:25 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
	{
		error_programm(2);
		return (0);
	}	
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	sms(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&philo->param->mutex_sms))
	{
		error_programm(6);
		return (0);
	}
	printf("\x1B[93m time (%lu) ms - philo (%d) :\x1B[94m  %s\n\033",
		(get_time() - philo->param->time_start), philo->id, str);
	if (pthread_mutex_unlock(&philo->param->mutex_sms))
	{
		error_programm(6);
		return (0);
	}
	return (1);
}

void	lock_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->mutex[philo->left]);
	sms(philo, "take forks🍴");
	pthread_mutex_lock(&philo->param->mutex[philo->right]);
}

void	unlock_mutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->param->mutex[philo->left]);
	pthread_mutex_unlock(&philo->param->mutex[philo->right]);
}

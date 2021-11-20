/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:17:21 by gjailbir          #+#    #+#             */
/*   Updated: 2021/11/19 20:19:02 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long wait_time)
{
	long	current_time;
	long	period;

	current_time = get_time();
	period = current_time + wait_time;
	while (period > current_time)
	{
		usleep(100);
		current_time = get_time();
	}
}

int	check_dead(t_param *param, int i)
{
	long	dead;

	dead = get_time() - param->philo[i].last_eat;
	if ((int)(dead) > param->time_to_live)
	{
		pthread_mutex_lock(&param->mutex_sms);
		printf("\x1B[91m time (%lu) - Philo (%d) is dead\n\033", dead, i + 1);
		return (1);
	}
	return (0);
}

void	*control_dead(void *param)
{
	t_param	*tmp;
	int		i;
	int		sum_eat;

	tmp = (t_param *)param;
	while (1)
	{
		i = 0;
		sum_eat = 0;
		while (i < tmp->number_of_philo)
		{
			if (check_dead(tmp, i) == 1)
				return (NULL);
			sum_eat += tmp->philo[i++].eat_count;
		}
		if (sum_eat == 0)
		{
			pthread_mutex_lock(&tmp->mutex_sms);
			printf("%s", "\x1B[92m All philosophers are fed up🤙\n\033");
			return (NULL);
		}
	}
}

void	destroy(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philo)
		pthread_mutex_destroy(&param->mutex[i++]);
	pthread_mutex_destroy(&param->mutex_sms);
}

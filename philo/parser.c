/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:17:05 by gjailbir          #+#    #+#             */
/*   Updated: 2021/11/16 23:07:52 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_routine(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	pthread_detach(philo->philo_thread);
	philo->last_eat = philo->param->time_start;
	while (1)
	{
		if (philo->eat_count != 0)
		{
			lock_mutex(philo);
			sms(philo, "eating");
			philo->eat_count--;
			my_sleep(philo->param->eat);
			unlock_mutex(philo);
			philo->last_eat = get_time();
			sms(philo, "sleeping");
			my_sleep(philo->param->sleep);
			sms(philo, "thinking");
		}
		else
			break ;
	}
	return (NULL);
}

void	create_pthread(t_param *param)
{
	int	i;

	i = -1;
	param->time_start = get_time();
	while (++i < param->number_of_philo)
	{
		if (i % 2 == 0)
			pthread_create(&param->philo[i].philo_thread, NULL, &start_routine,
				  &param->philo[i]);
		usleep(30);
	}
	i = -1;
	usleep(30);
	while (++i < param->number_of_philo)
	{
		if (i % 2 == 1)
			pthread_create(&param->philo[i].philo_thread, NULL, &start_routine,
				  &param->philo[i]);
		usleep(30);
	}
	pthread_create(&param->check_death_thread, NULL, &control_dead, param);
	pthread_join(param->check_death_thread, NULL);
	destroy(param);
}

void	init_philo(t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->number_of_philo)
	{
		param->philo[i].eat_count = param->number_of_meals;
		param->philo[i].id = i + 1;
		param->philo[i].param = param;
		if (pthread_mutex_init(&param->mutex[i], NULL) != 0)
			error_programm(4);
		param->philo[i].left = i;
		if (i < param->number_of_philo - 1)
			param->philo[i].right = (i + 1);
	}
	if (param->number_of_philo != 1)
		param->philo[--i].right = 0;
	if (param->number_of_philo == 1)
		param->philo[0].right = 0;
}

int	parser(char **argv, t_param *param)
{
	param->number_of_philo = ft_atoi(argv[1]);
	param->time_to_live = ft_atoi(argv[2]);
	param->eat = ft_atoi(argv[3]);
	param->sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->number_of_meals = ft_atoi(argv[5]);
	else
		param->number_of_meals = -1;
	if (param->number_of_philo < 1 || param->time_to_live < 1 || param->eat < 1
		|| param->sleep < 1 || param->number_of_meals == 0)
	{
		error_programm(3);
		return (0);
	}
	if (pthread_mutex_init(&param->mutex_sms, NULL))
		error_programm(4);
	return (1);
}

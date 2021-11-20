/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:16:55 by gjailbir          #+#    #+#             */
/*   Updated: 2021/11/18 21:54:36 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	memory_allocation(t_param *param)
{
	param->philo = malloc(sizeof(t_philo) * param->number_of_philo);
	param->mutex = malloc(sizeof(pthread_mutex_t) * param->number_of_philo);
	if (!param->philo || !param->mutex)
	{
		error_programm(1);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_param		param;

	if (argc == 5 || argc == 6)
	{
		if (!init_params(argv, &param) || !memory_allocation(&param) \
		|| (!init_philo(&param)))
			return (0);
		create_pthread(&param);
		free(param.philo);
		free(param.mutex);
	}
	else
		error_programm(3);
	return (0);
}

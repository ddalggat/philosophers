/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:04:00 by gjailbir          #+#    #+#             */
/*   Updated: 2021/11/18 21:58:46 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				id;
	int				eat_count;
	unsigned long	last_eat;
	int				left;
	int				right;
	struct s_param	*param;
}		t_philo;

typedef struct s_param
{
	pthread_t		check_death_thread;
	int				number_of_philo;
	int				time_to_live;
	int				eat;
	int				sleep;
	int				number_of_meals;
	unsigned long	time_start;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_sms;
}		t_param;

//***//utils_functions\\***//
int				ft_isdigit(char c);
int				ft_atoi(const char *s);
void			error_programm(int i);

//***//philo_1_functions\\***//
long			get_time(void);
int				sms(t_philo *philo, char *str);
void			lock_mutex(t_philo *philo);
void			unlock_mutex(t_philo *philo);

//***//philo_2_functions\\***//
void			my_sleep(long time);
void			*control_dead(void *param);
void			destroy(t_param *param);

//***//parser_functions\\***//
int				init_params(char **argv, t_param *param);
int				init_philo(t_param *param);
void			create_pthread(t_param *param);
void			*start_activity(void *a);

#endif

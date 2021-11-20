/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjailbir <gjailbir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:54:51 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/11/21 00:23:05 by gjailbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_semaphs
{
	sem_t			*forks;
	sem_t			*checkd;
	sem_t			*write_semaphore;
}					t_semaphs;

typedef struct s_params
{
	long			number_of_philo;
	long			life_time;
	long			eat_time;
	long			sleep_time;
	long			number_of_meals;
	int				death_flag;
}					t_params;

typedef struct s_philos
{
	int				philo_id;
	long			start;
	long			last;
	t_semaphs		*semaphore;
	t_params		*params;
	pid_t			*pid;
	pthread_t		philosopher;
}					t_philos;

typedef struct s_all
{
	long			time;
	pid_t			*pid;
	t_semaphs		*semaphore;
	t_params		*params;
	t_philos		*philosophers;
}					t_all;

int			main(int ac, char **av);
void		philosopher_eats(t_philos *philo);
void		philosopher_sleeps(t_philos *philo);
void		philosopher_thinks(t_philos *philo);
int			philosopher_full(t_philos *philo, int *i);
void		*check_death(void *philo);
int			init_params(t_all *all, char **arv, int arc);
int			init_sems(t_all *all);
int			init_philos(t_all *all);
void		processes(t_philos *philo);
void		wait_loop(t_all *all);
int			start_philosopher(t_all *all);
int			ft_atoi(char *str);
int			is_digit(char c);
int			out_error(char *err);
int			ft_strlen(char *str);
void		free_all(t_all *all);
long		time_fix(void);
void		sleep_fix(long wait_time);
void		error_programm(int i);

#endif

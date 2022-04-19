/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:40:58 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/18 12:56:55 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_initialize(t_s *s)
{
	int	i;

	s->args.init_time = ft_get_time();
	pthread_mutex_init(&s->args.write, NULL);
	pthread_mutex_init(&s->args.dead, NULL);
	pthread_mutex_init(&s->args.check_arg, NULL);
	s->args.end = 0;
	s->args.thread_in_progress = 0;
	s->args.nb_finish = 0;
	i = -1;
	while (++i < s->args.nb_philo)
	{
		s->philo[i].id = i + 1;
		s->philo[i].p_a = &s->args;
		s->philo[i].nb_eat = 0;
		s->philo[i].elapsed_time = s->args.init_time;
		pthread_mutex_init(&s->philo[i].left_fork, NULL);
		if (s->args.nb_philo == 1)
			return ;
		if (i == s->args.nb_philo - 1)
			s->philo[i].right_fork = &s->philo[0].left_fork;
		else
			s->philo[i].right_fork = &s->philo[i + 1].left_fork;
	}
}

void	ft_usleep(t_arg *arg, long int time)
{
	long int	start;

	start = 0;
	start = ft_get_time();
	while ((ft_get_time() - start) < time && ft_check_is_dead(arg) == 0)
		usleep(10);
}

long int	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_return(NULL, "gettimeofday error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print_statut(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->p_a->write);
	if (ft_check_is_dead(philo->p_a) == 0)
	{
		pthread_mutex_lock(&philo->p_a->check_arg);
		if (philo->nb_eat != philo->p_a->nb_must_eat)
			printf("%ld %d %s\n", ft_get_time() - philo->p_a->init_time,
				philo->id, msg);
		pthread_mutex_unlock(&philo->p_a->check_arg);
	}
	pthread_mutex_unlock(&philo->p_a->write);
}

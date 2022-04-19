/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 13:39:47 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/16 15:04:15 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_thread_death(t_s *s)
{
	int	ret;

	pthread_mutex_lock(&s->args.dead);
	pthread_mutex_lock(&s->args.check_arg);
	ret = s->args.thread_in_progress;
	pthread_mutex_unlock(&s->args.check_arg);
	pthread_mutex_unlock(&s->args.dead);
	return (ret);
}

void	ft_count_thread(t_philo *philo, int u)
{
	pthread_mutex_lock(&philo->p_a->dead);
	pthread_mutex_lock(&philo->p_a->check_arg);
	if (u == 1)
		philo->p_a->thread_in_progress++;
	else if (u == -1)
		philo->p_a->thread_in_progress--;
	pthread_mutex_unlock(&philo->p_a->check_arg);
	pthread_mutex_unlock(&philo->p_a->dead);
}

void	*ft_check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_count_thread(philo, 1);
	ft_usleep(philo->p_a, philo->p_a->time_to_die + 1);
	if (ft_check_is_dead(philo->p_a) == 0)
	{
		pthread_mutex_lock(&philo->p_a->check_arg);
		if (ft_get_time() - philo->elapsed_time >= philo->p_a->time_to_die)
		{
			pthread_mutex_unlock(&philo->p_a->check_arg);
			ft_print_statut(philo, "died");
			pthread_mutex_lock(&philo->p_a->check_arg);
			philo->p_a->end = philo->id;
			pthread_mutex_unlock(&philo->p_a->check_arg);
			ft_count_thread(philo, -1);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->p_a->check_arg);
	}
	ft_count_thread(philo, -1);
	return (NULL);
}

int	ft_check_is_dead(t_arg *arg)
{
	int	ret;

	ret = -1;
	pthread_mutex_lock(&arg->check_arg);
	if (arg->end == 0)
		ret = 0;
	else
		ret = 1;
	pthread_mutex_unlock(&arg->check_arg);
	return (ret);
}

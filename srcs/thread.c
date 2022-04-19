/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:51:27 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/16 14:33:50 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_round_table(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	ft_print_statut(philo, "has taken a fork");
	if (!philo->right_fork)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (ft_usleep(philo->p_a, philo->p_a->time_to_die + 42));
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print_statut(philo, "has taken a fork");
	ft_print_statut(philo, "is eating");
	pthread_mutex_lock(&philo->p_a->check_arg);
	philo->elapsed_time = ft_get_time();
	pthread_mutex_unlock(&philo->p_a->check_arg);
	ft_usleep(philo->p_a, philo->p_a->time_to_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print_statut(philo, "is slepping");
	ft_usleep(philo->p_a, philo->p_a->time_to_sleep);
	ft_print_statut(philo, "is thiking");
}

void	*ft_thread(void *arg)
{
	t_philo		*philo;
	pthread_t	check_death;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->p_a, philo->p_a->time_to_eat / 10);
	while (ft_check_is_dead(philo->p_a) == 0)
	{
		pthread_create(&check_death, NULL, ft_check_death, arg);
		pthread_detach(check_death);
		ft_round_table(philo);
		pthread_mutex_lock(&philo->p_a->check_arg);
		if (philo->nb_eat == philo->p_a->nb_must_eat)
		{
			philo->p_a->nb_finish++;
			pthread_mutex_unlock(&philo->p_a->check_arg);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->p_a->check_arg);
	}
	return (NULL);
}

int	ft_thread_init(t_s *s)
{
	int	i;

	i = -1;
	while (++i < s->args.nb_philo)
		pthread_create(&s->philo[i].thread_id, NULL, ft_thread, &s->philo[i]);
	return (0);
}

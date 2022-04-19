/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:27:14 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/16 15:06:51 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *str)
{
	printf("Error : %s\n", str);
	return (0);
}

int	ft_exit_bis(t_s *s)
{
	int	i;

	while (ft_check_thread_death(s) != 0)
		ft_usleep(&s->args, 10);
	pthread_mutex_destroy(&s->args.write);
	pthread_mutex_destroy(&s->args.dead);
	pthread_mutex_destroy(&s->args.check_arg);
	i = -1;
	while (++i < s->args.nb_philo)
		pthread_mutex_destroy(&s->philo[i].left_fork);
	free(s->philo);
	return (0);
}

int	ft_return(t_s *s, char *msg)
{
	int	i;

	if (msg)
		printf("%s\n", msg);
	if (s != NULL)
	{
		i = -1;
		while (++i < s->args.nb_philo)
			pthread_join(s->philo[i].thread_id, NULL);
		if (ft_check_is_dead(&s->args) == 0 && s->args.nb_finish
			== s->args.nb_philo)
			printf("Each philosopher ate %ld time(s)\n", s->args.nb_must_eat);
		return (ft_exit_bis(s));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_s	s;

	if ((ft_parse_args(ac, av, &s)))
		return (ft_exit("Invalid Arguments"));
	s.philo = malloc(sizeof(t_philo) * s.args.nb_philo);
	if (!s.philo)
		return (ft_exit("Malloc error"));
	ft_initialize(&s);
	ft_thread_init(&s);
	return (ft_return(&s, NULL));
}

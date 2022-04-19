/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:08:25 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/16 14:37:54 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_verif(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_strlen(av[i]) <= 0 || ft_isalldigit(av[i]))
			return (1);
	}
	return (0);
}

int	ft_parse_args(int ac, char **av, t_s *s)
{
	if ((ac == 5 || ac == 6) && !ft_verif(av))
	{
		s->args.nb_philo = ft_atoi(av[1]);
		s->args.time_to_die = ft_atoi(av[2]);
		s->args.time_to_eat = ft_atoi(av[3]);
		s->args.time_to_sleep = ft_atoi(av[4]);
		s->args.nb_must_eat = -1;
		if (ac == 6)
			s->args.nb_must_eat = ft_atoi(av[5]);
		if (s->args.nb_philo < 0 || s->args.time_to_die < 0
			|| s->args.time_to_eat < 0 || s->args.time_to_sleep < 0)
			return (1);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:07:49 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/16 09:49:08 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	u;
	int	nb;

	u = 1;
	nb = 0;
	while (*str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t'
		|| *str == '\v' || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			u = u * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
		nb = nb * 10 + (*str++ - 48);
	return (nb * u);
}

int	ft_isalldigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

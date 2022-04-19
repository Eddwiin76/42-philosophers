/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:22:04 by tpierre           #+#    #+#             */
/*   Updated: 2021/08/16 09:49:25 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_arg
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long int			nb_must_eat;
	long int			init_time;
	int					nb_finish;
	int					end;
	pthread_mutex_t		write;
	pthread_mutex_t		dead;
	pthread_mutex_t		check_arg;
	pthread_t			death_id;
	int					thread_in_progress;
}				t_arg;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	long int			nb_eat;
	long int			elapsed_time;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	t_arg				*p_a;
}				t_philo;

typedef struct s_s
{
	t_philo				*philo;
	t_arg				args;
}				t_s;

int			ft_verif(char **av);
int			ft_parse_args(int ac, char **av, t_s *s);
int			ft_isalldigit(char *str);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		ft_initialize(t_s *s);
long int	ft_get_time(void);
void		ft_print_statut(t_philo *philo, char *msg);
int			ft_thread_init(t_s *s);
int			ft_check_is_dead(t_arg *arg);
void		ft_usleep(t_arg *arg, long int time);
int			ft_exit(char *str);
int			ft_return(t_s *s, char *msg);
void		*ft_check_death(void *arg);
int			ft_check_thread_death(t_s *s);

#endif

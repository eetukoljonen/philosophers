/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:48:40 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/12 14:53:31 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define THREAD_FAIL "Failed to create a thread\n"
# define INIT_FAIL "Failed to initialize structs\n"
# define RESOURCE_FAIL "Failed to get resrc\n"
# define BAD_INPUT "Wrong input\n"
# define WRONG_FORMAT "Wrong format\n"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/*
**	struct for all the arguments and mutexes
*/

typedef struct s_resrc
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				phils;
	int				eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	*stop_mutex;
	struct timeval	start;
}					t_resrc;

/*
**	struct for philosopher that contains the necessary data for philospher
*/

typedef struct s_phil
{
	pthread_t		phil;
	struct timeval	eat;
	int				number;
	int				stop;
	int				how_many_times;
	int				fork;
	t_resrc			*resrc;
}					t_phil;

/*
**	init
*/
t_phil		*init_philosophers(t_resrc *resrc);
t_resrc		*get_resrc(int argc, char **argv);
void		check_input(int argc, char **argv);
/*
**	utils
*/
int			ft_is_number(char *s);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
/*
**	threads
*/
void		begin_simulation(t_phil	*phils);
void		stop_simulation(t_phil *phils);
/*
**	eatsleepthink
*/
void		my_sleep(int time, t_phil *phil);
void		*eatsleepthink(void *arg);
void		eat(t_phil *phil);
void		print_statement(char *s, t_phil *phil);
/*
**	free
*/
void		free_exit(char *s, t_phil *phil);
void		error_exit(char *s);
/*
**	main
*/
void		check_phil_status(t_phil *phil);
int		check_meals(t_phil *phil, int eat_ctr);
void		philosopher_died(t_phil *phil, int ctr);
#endif
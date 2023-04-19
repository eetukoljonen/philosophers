/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:21:20 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/19 17:14:42 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	this function checks if each philosopher has eaten
**	[number_of_times_each_philosopher_must_eat] amount of times
**	and returns one when true
*/

int	check_meals(t_phil *phil)
{
	int	eat_ctr;
	int	ctr;

	ctr = 0;
	eat_ctr = 0;
	if (phil->resrc->eat > 0)
	{
		while (ctr < phil->resrc->phils)
		{
			if (phil[ctr].how_many_times >= phil->resrc->eat)
				eat_ctr++;
			if (eat_ctr == phil->resrc->phils)
			{
				pthread_mutex_lock(&phil[ctr].resrc->stop_mutex);
				phil->resrc->stop = 1;
				pthread_mutex_unlock(&phil[ctr].resrc->stop_mutex);
				return (1);
			}
			ctr++;
		}
	}
	return (0);
}

/*
**	this function is called when the time_to_die amount of
**	time has passed since the beginning of last meal
**	we also use mutexes so there wont be any data races
*/

void	philosopher_died(t_phil *phil)
{
	pthread_mutex_lock(&phil->resrc->stop_mutex);
	phil->dead = 1;
	print_statement("died\n", phil);
	phil->resrc->stop = 1;
	pthread_mutex_unlock(&phil->resrc->stop_mutex);
}

/*
**	this function check the status of each philosopher
**	wether the philosopher is dead or all the philosopher has eaten
**	all the meals that was given as an argument
*/

void	check_phil_status(t_phil *phil)
{
	struct timeval	t;
	int				ctr;

	ctr = 0;
	while (!phil->resrc->stop)
	{
		if (check_meals(phil))
			break ;
		while (ctr < phil->resrc->phils && !phil->resrc->stop)
		{
			gettimeofday(&t, NULL);
			pthread_mutex_lock(&phil[ctr].resrc->eat_mutex);
			if (((t.tv_sec * 1000 + t.tv_usec / 1000)
					- (phil[ctr].eat.tv_sec * 1000 + phil[ctr].eat.tv_usec
						/ 1000)) >= phil[ctr].resrc->time_to_die)
				philosopher_died(&phil[ctr]);
			pthread_mutex_unlock(&phil[ctr].resrc->eat_mutex);
			ctr++;
		}
		ctr = 0;
	}
}

/*
**	this is a program called philosophers which tackles
**	the famous dining philosopher problem
**	run ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
**	[number_of_times_each_philosopher_must_eat] last argument is optional
*/

int	main(int argc, char **argv)
{
	t_phil	*phils;
	t_resrc	*resrc;

	if (argc != 5 && argc != 6)
		error_exit(WRONG_FORMAT);
	resrc = get_resrc(argc, argv);
	phils = init_philosophers(resrc);
	begin_simulation(phils);
	return (0);
}

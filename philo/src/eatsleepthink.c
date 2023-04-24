/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepthink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:47:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/24 12:46:42 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	this function prints the time that has passed since
**	the start of the simulation, philosopher number and
**	the statement
*/

void	print_statement(char *s, t_phil *phil)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&phil->resrc->print);
	pthread_mutex_lock(&phil->resrc->stop_mutex[phil->number - 1]);
	if (!phil->stop)
		printf("%ld %d %s", ((time.tv_sec * 1000 + time.tv_usec / 1000)
				- (phil->resrc->start.tv_sec * 1000
					+ phil->resrc->start.tv_usec / 1000)), phil->number, s);
	pthread_mutex_unlock(&phil->resrc->print);
	pthread_mutex_unlock(&phil->resrc->stop_mutex[phil->number - 1]);
}

/*
**	this function is the eat function and the proper use
**	of mutexes solves the problem that philosophers
**	that sits next to eachother wont be eating at the same time
*/

void	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->resrc->fork[phil->fork]);
	print_statement("has taken a fork\n", phil);
	pthread_mutex_lock(&phil->resrc->fork[(phil->fork + 1)
		% phil->resrc->phils]);
	print_statement("has taken a fork\n", phil);
	pthread_mutex_lock(&phil->resrc->eat_mutex);
	print_statement("is eating\n", phil);
	gettimeofday(&phil->eat, NULL);
	pthread_mutex_unlock(&phil->resrc->eat_mutex);
	my_sleep(phil->resrc->time_to_eat, phil);
	phil->how_many_times += 1;
	pthread_mutex_unlock(&phil->resrc->fork[(phil->fork + 1)
		% phil->resrc->phils]);
	pthread_mutex_unlock(&phil->resrc->fork[phil->fork]);
}

/*
**	this is the routine every thread goes through
**	and we desynchronize every odd numbered philosopher
**	to avoid deadlocks and careful use of mutexes avoids
**	data races
*/

void	*eatsleepthink(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->number % 2 && phil->resrc->phils > 1)
	{
		if (phil->resrc->time_to_eat > 10)
			my_sleep(phil->resrc->time_to_eat / 2, phil);
		else
			my_sleep(phil->resrc->time_to_eat, phil);
	}
	while (1)
	{
		eat(phil);
		print_statement("is sleeping\n", phil);
		my_sleep(phil->resrc->time_to_sleep, phil);
		print_statement("is thinking\n", phil);
		pthread_mutex_lock(&phil->resrc->stop_mutex[phil->number - 1]);
		if (phil->stop)
		{
			pthread_mutex_unlock(&phil->resrc->stop_mutex[phil->number - 1]);
			break ;
		}
		pthread_mutex_unlock(&phil->resrc->stop_mutex[phil->number - 1]);
	}
	return (NULL);
}

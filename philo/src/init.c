/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:36:33 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/19 17:23:11 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	this function check that the input is correctly
**	formatted
*/

void	check_input(int argc, char **argv)
{
	int	ctr;

	ctr = 1;
	while (ctr < argc)
		if (!ft_is_number(argv[ctr++]))
			error_exit(BAD_INPUT);
}

/*
**	this function gets the command line arguments
**	into a struct that every philosopher has access to
*/

t_resrc	*get_resrc(int argc, char **argv)
{
	t_resrc	*resrc;

	check_input(argc, argv);
	resrc = (t_resrc *)malloc(sizeof(t_resrc));
	if (!resrc)
		error_exit(RESOURCE_FAIL);
	resrc->phils = ft_atoi(argv[1]);
	resrc->time_to_die = ft_atoi(argv[2]);
	resrc->time_to_eat = ft_atoi(argv[3]);
	resrc->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		resrc->eat = ft_atoi(argv[5]);
	else
		resrc->eat = -1;
	resrc->stop = 0;
	resrc->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* resrc->phils);
	if (!resrc->fork)
	{
		free(resrc);
		error_exit(RESOURCE_FAIL);
	}
	return (resrc);
}

/*
**	this function initializes array of pihlo structs
**	and also initializes all the mutexes we are going to
**	be needing
*/

t_phil	*init_philosophers(t_resrc *resrc)
{
	int		ctr;
	t_phil	*phils;

	ctr = 0;
	phils = (t_phil *)malloc(sizeof(t_phil) * resrc->phils);
	if (!phils)
		free_exit(INIT_FAIL, phils);
	while (ctr < resrc->phils)
	{
		if (pthread_mutex_init(&resrc->fork[ctr], NULL) != 0)
			free_exit(INIT_FAIL, phils);
		phils[ctr].resrc = resrc;
		phils[ctr].how_many_times = 0;
		phils[ctr].number = ctr + 1;
		phils[ctr].fork = ctr;
		ctr++;
	}
	if (pthread_mutex_init(&resrc->eat_mutex, NULL) != 0)
		free_exit(INIT_FAIL, phils);
	if (pthread_mutex_init(&resrc->print, NULL) != 0)
		free_exit(INIT_FAIL, phils);
	if (pthread_mutex_init(&resrc->stop_mutex, NULL) != 0)
		free_exit(INIT_FAIL, phils);
	return (phils);
}

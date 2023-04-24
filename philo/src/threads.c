/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:43:45 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/24 13:31:22 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	this function stops the simulation by waiting for
**	every thread to finish and then we destroy every mutex
**	and free everything for a clean exit
*/

void	stop_simulation(t_phil *phils)
{
	int	ctr;

	ctr = -1;
	if (phils->resrc->phils == 1)
		pthread_detach(phils[0].phil);
	else
		while (++ctr < phils->resrc->phils)
			pthread_join(phils[ctr].phil, NULL);
	ctr = -1;
	while (++ctr < phils->resrc->phils)
	{
		pthread_mutex_destroy(&phils->resrc->fork[ctr]);
		pthread_mutex_destroy(&phils->resrc->stop_mutex[ctr]);
	}
	pthread_mutex_destroy(&phils->resrc->eat_mutex);
	pthread_mutex_destroy(&phils->resrc->print);
	free(phils->resrc->fork);
	free(phils->resrc->stop_mutex);
	free(phils->resrc);
	free(phils);
}

/*
**	this function starts the simulation by creating all the threads
*/

void	begin_simulation(t_phil	*phils)
{
	int	ctr;

	ctr = 0;
	gettimeofday(&phils[ctr].resrc->start, NULL);
	while (ctr < phils[0].resrc->phils)
	{
		gettimeofday(&phils[ctr].eat, NULL);
		if (pthread_create(&phils[ctr].phil, NULL,
				eatsleepthink, &phils[ctr]) != 0)
			free_exit(THREAD_FAIL, phils);
		ctr++;
	}
	check_phil_status(phils);
	stop_simulation(phils);
}

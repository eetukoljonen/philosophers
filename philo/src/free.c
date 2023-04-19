/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:48:46 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/19 17:20:57 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	this function prints the error message and exits
**	the program
*/

void	error_exit(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

/*
**	this function just frees all allocated memory
*/

void	free_exit(char *s, t_phil *phil)
{
	if (phil)
	{
		if (phil->resrc)
		{
			if (phil->resrc->fork)
				free(phil->resrc->fork);
			free(phil->resrc);
		}
		free(phil);
	}
	error_exit(s);
}

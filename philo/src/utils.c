/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:53 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/20 19:14:58 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	sleeps a given amount of time in millsecons
**	reason we use this insted of just usleep
**	is that usleep looses its precision with big
**	numbers
*/

void	my_sleep(int time, t_phil *phil)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		if (((end.tv_sec * 1000 + end.tv_usec / 1000)
				- (start.tv_sec * 1000 + start.tv_usec / 1000)) >= time)
			break ;
		usleep(100);
		pthread_mutex_lock(&phil->resrc->stop_mutex);
		if (phil->resrc->stop)
		{
			pthread_mutex_unlock(&phil->resrc->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&phil->resrc->stop_mutex);
	}
}

/*
**	converts a string to integer value
*/

int	ft_atoi(const char *str)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = sign * -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (result > 2147483647)
		error_exit(BAD_INPUT);
	return (result * sign);
}

/*
**	writes a string to a specific file descriptor
*/

void	ft_putstr_fd(char *s, int fd)
{
	if (s != 0)
	{
		while (*s != 0)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

/*
**	checks if the string is a digit
*/

int	ft_is_number(char *s)
{
	if (!*s || *s == '0' || !ft_atoi(s))
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

/*
**	checks if the character is a digit
*/

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

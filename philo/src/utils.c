/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:53 by ekoljone          #+#    #+#             */
/*   Updated: 2023/04/25 13:19:03 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	my implementation of strncmp
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ctr;

	ctr = 0;
	if (n == 0)
		return (0);
	while (ctr < n - 1 && s1[ctr] == s2[ctr]
		&& s1[ctr] != '\0' && s2[ctr] != '\0')
		ctr++;
	return ((unsigned char)s1[ctr] - (unsigned char)s2[ctr]);
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
**	checks if the string is a number
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

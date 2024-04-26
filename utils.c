/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:29:10 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/25 16:46:10 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	max_check(long nbr, long temp, int sign)
{
	if (nbr < temp)
	{
		if (sign > 0)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nbr;
	long	previous;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	if (*str < '0' && *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		previous = nbr;
		nbr = nbr * 10 + *str - '0';
		if (max_check(nbr, previous, sign) != 1)
			return (max_check(nbr, previous, sign));
		str++;
	}
	return ((int)nbr * sign);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, GET_TIME_ERR, 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

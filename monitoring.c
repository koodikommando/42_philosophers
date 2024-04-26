/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:28:56 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/26 16:10:03 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	man_down(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->p->time_to_die)
	{
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_if_dead(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->philos_count)
	{
		if (man_down(&p->philos[i]) == 1)
		{
			pthread_mutex_lock(&p->dead_lock);
			p->dead_philosopher = 1;
			pthread_mutex_unlock(&p->dead_lock);
			pthread_mutex_lock(&p->write_lock);
			printf("%lu %d died\n", get_current_time() - p->start_time,
				p->philos[i].id);
			pthread_mutex_unlock(&p->write_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_ate(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->philos_count)
	{
		pthread_mutex_lock(&p->philos[i].meal_lock);
		if (p->philos[i].times_eaten < p->meals_left)
		{
			pthread_mutex_unlock(&p->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&p->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_lock(&p->dead_lock);
	p->dead_philosopher = 1;
	pthread_mutex_unlock(&p->dead_lock);
	pthread_mutex_unlock(&p->philos[i].meal_lock);
	return (1);
}

void	*monitoring(void *program)
{
	t_program	*p;

	p = (t_program *)program;
	ft_usleep(10);
	while (1)
	{
		if (p->meals_left != -1)
			if (all_ate(p) == 1)
				break ;
		if (check_if_dead(p) == 1)
			break ;
	}
	return (NULL);
}

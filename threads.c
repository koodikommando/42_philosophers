/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:29:07 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/25 15:18:35 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->p->dead_lock);
	if (philo->p->dead_philosopher == 1)
	{
		pthread_mutex_unlock(&philo->p->dead_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->p->dead_lock);
		return (0);
	}
}

static void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo))
	{
		eat(philo);
		if (is_dead(philo))
			break ;
		dream(philo);
		if (is_dead(philo))
			break ;
		think(philo);
	}
	return (NULL);
}

static int	destroy_mutexes(t_program *p, char *msg)
{
	int	i;

	i = 0;
	while (i < p->philos_count)
	{
		pthread_mutex_destroy(&p->forks[i]);
		pthread_mutex_destroy(&p->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&p->dead_lock);
	pthread_mutex_destroy(&p->write_lock);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (1);
}

static int	thread_creation_fail(t_program *p)
{
	write(2, THREAD_CREATE_ERR, ft_strlen(THREAD_CREATE_ERR));
	pthread_mutex_lock(&p->dead_lock);
	p->dead_philosopher = 1;
	pthread_mutex_unlock(&p->dead_lock);
	if (pthread_join(p->monitor, NULL) != 0)
		return (destroy_mutexes(p, THREAD_JOIN_ERR));
	while (p->threads_created > 0)
	{
		p->threads_created--;
		if (pthread_join(p->philos[p->threads_created].thread, NULL) != 0)
			return (destroy_mutexes(p, THREAD_JOIN_ERR));
	}
	return (destroy_mutexes(p, NULL));
}

int	create_threads(t_program *p)
{
	if (p->meals_left == 0)
		return (0);
	if (pthread_create(&p->monitor, NULL, &monitoring, p) != 0)
		return (destroy_mutexes(p, THREAD_CREATE_ERR));
	while (p->threads_created < p->philos_count)
	{
		if (pthread_create(&p->philos[p->threads_created].thread, NULL,
				&routine, &p->philos[p->threads_created]) != 0)
			return (thread_creation_fail(p));
		p->threads_created++;
	}
	if (pthread_join(p->monitor, NULL) != 0)
		return (destroy_mutexes(p, THREAD_JOIN_ERR));
	while (p->threads_created > 0)
	{
		p->threads_created--;
		if (pthread_join(p->philos[p->threads_created].thread, NULL) != 0)
			return (destroy_mutexes(p, THREAD_JOIN_ERR));
	}
	destroy_mutexes(p, NULL);
	return (0);
}

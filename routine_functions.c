/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:36:14 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/25 14:49:32 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->p->write_lock);
	time = get_current_time() - philo->p->start_time;
	if (!is_dead(philo))
	{
		printf("%lu %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(&philo->p->write_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->p->philos_count == 1)
	{
		ft_usleep(philo->p->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->p->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->p->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

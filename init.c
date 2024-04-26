/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:28:53 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/25 16:46:30 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philos(t_program *program, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < program->philos_count)
	{
		philos[i].p = program;
		philos[i].id = i + 1;
		philos[i].is_dead = &program->dead_philosopher;
		philos[i].times_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].right_fork = &program->forks[i];
		if (i == 0)
			philos[i].left_fork = &program->forks[program->philos_count - 1];
		else
			philos[i].left_fork = &program->forks[i - 1];
		philos[i].last_meal = get_current_time();
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, int argc, char **argv)
{
	program->dead_philosopher = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	program->philos_count = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->meals_left = ft_atoi(argv[5]);
	else
		program->meals_left = -1;
	init_philos(program, program->philos);
	program->threads_created = 0;
	program->start_time = get_current_time();
}

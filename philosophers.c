/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:28:59 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/25 16:48:57 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (write(2, PHILO_COUNT_ERR, ft_strlen(PHILO_COUNT_ERR)));
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, TIME_TO_DIE_ERR, ft_strlen(TIME_TO_DIE_ERR)));
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, TIME_TO_EAT_ERR, ft_strlen(TIME_TO_EAT_ERR)));
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, TIME_TO_SLEEP_ERR, ft_strlen(TIME_TO_SLEEP_ERR)));
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, TIMES_TO_EAT_ERR, ft_strlen(TIMES_TO_EAT_ERR)));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_program		program;
	t_philo			philosophers[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (1);
	if (check_args(argv) != 0)
		return (1);
	program.philos = philosophers;
	program.forks = forks;
	init_program(&program, argc, argv);
	init_forks(program.forks, &program);
	if (create_threads(&program) != 0)
		return (1);
	return (0);
}

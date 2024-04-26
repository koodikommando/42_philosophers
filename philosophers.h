/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:29:03 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/25 16:46:45 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define PHILO_MAX 200

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define PHILO_COUNT_ERR "Error: Invalid number of philosophers\n"
# define TIME_TO_DIE_ERR "Error: Invalid time to die\n"
# define TIME_TO_EAT_ERR "Error: Invalid time to eat\n"
# define TIME_TO_SLEEP_ERR "Error: Invalid time to sleep\n"
# define TIMES_TO_EAT_ERR "Error: Invalid number of times to eat\n"
# define ARG_COUNT_ERR "Error: Invalid number of arguments\n"
# define GET_TIME_ERR "Error: gettimeoftheday failed\n"
# define THREAD_CREATE_ERR "Error: Thread creation failed\n"
# define THREAD_JOIN_ERR "Error: Thread join failed\n"

struct	s_program;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					*is_dead;
	int					eating;
	size_t				last_meal;
	int					times_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_lock;
	struct s_program	*p;
}	t_philo;

typedef struct s_program
{
	int				philos_count;
	int				dead_philosopher;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				threads_created;
	int				meals_left;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	size_t			start_time;
}	t_program;

int		ft_atoi(const char *str);
void	init_program(t_program *program, int argc, char **argv);
int		create_threads(t_program *program);
void	init_forks(pthread_mutex_t *forks, t_program *program);
void	print_message(char *str, t_philo *philo, int id);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	*monitoring(void *pointer);
void	destory_all(char *str, t_program *program, pthread_mutex_t *forks);
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	print_message(char *str, t_philo *philo, int id);
int		is_dead(t_philo *philo);
size_t	ft_strlen(const char *s);

#endif
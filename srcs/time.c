/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:33 by arthur            #+#    #+#             */
/*   Updated: 2021/07/14 17:36:36 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

long long int	utc_time_in_usec(struct timeval time)
{
	return (((long long int)time.tv_sec * 1000) + (time.tv_usec / 1000));
}

struct timeval	now(void)
{
	struct timeval	n;

	gettimeofday(&n, NULL);
	return (n);
}

long long int	elapsed_time(struct timeval start)
{
	return (utc_time_in_usec(now()) - utc_time_in_usec(start));
}

void	sleep_time(int time)
{
	long long int	n;

	n = utc_time_in_usec(now());
	while (utc_time_in_usec(now()) - n < time)
		usleep(100);
}

/*
** NORM
**
*/

void	kill_philo(t_philo *philo, int *alive)
{
	pthread_mutex_lock(philo->aliver);
	philo->is_alive = 0;
	*alive = 0;
	pthread_mutex_unlock(philo->aliver);
	mutex_printer(philo, "died\n", elapsed_time(philo->conf->elapsed)
		- 1, philo->id);
	philo->conf->running = 0;
}

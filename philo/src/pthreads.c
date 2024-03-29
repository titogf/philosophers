/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:30:39 by gfernand          #+#    #+#             */
/*   Updated: 2023/06/20 17:59:15 by gfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*pthread(void *data);
static void	processes(t_philo *ph);
static void	processes_2(t_philo *ph);

int	create_thread(t_d *d)
{
	int	i;
	int	t;

	i = -1;
	while (++i < d->arg.total_ph)
	{
		d->ph[i].a = &d->arg;
		t = pthread_create(&d->ph[i].th_id, NULL, pthread, &d->ph[i]);
		if (t != 0)
		{
			printf("Pthread error\n");
			return (0);
		}
	}
	return (1);
}

static void	*pthread(void *data)
{
	t_philo	*ph;

	ph = (t_philo *) data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->a->die / 8);
	while (!ph->a->stop_process)
	{
		processes(ph);
		if (++ph->nb_eat == ph->a->m_eat)
		{
			pthread_mutex_lock(&ph->a->ph_finish);
			++ph->a->nb_finished;
			pthread_mutex_unlock(&ph->a->ph_finish);
		}
	}
	return (ph);
}

static void	processes(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(&ph->a->write_stats);
	print_stats(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->a->write_stats);
	if (!ph->r_f)
		return ;
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->a->write_stats);
	print_stats(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->a->write_stats);
	pthread_mutex_lock(&ph->a->write_stats);
	print_stats(ph, "is eating");
	pthread_mutex_unlock(&ph->a->write_stats);
	pthread_mutex_lock(&ph->a->time_to_eat);
	ph->time_eat = actual_time();
	pthread_mutex_unlock(&ph->a->time_to_eat);
	ft_usleep(ph->a->eat);
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_unlock(ph->r_f);
	processes_2(ph);
}

static void	processes_2(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->write_stats);
	print_stats(ph, "is sleeping");
	pthread_mutex_unlock(&ph->a->write_stats);
	ft_usleep(ph->a->sleep);
	pthread_mutex_lock(&ph->a->write_stats);
	print_stats(ph, "is thinking");
	pthread_mutex_unlock(&ph->a->write_stats);
}

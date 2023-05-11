/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:07:49 by marvin            #+#    #+#             */
/*   Updated: 2023/05/11 19:07:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long int	less_time_philosophers(t_geral **geral)
{
	t_geral			*temp;
	long int		num;
	struct timeval	time_start;
	struct timeval	time_end;

	temp = *geral;
	gettimeofday(&time_start, NULL);
	while (temp != NULL)
	{
		pthread_mutex_lock(&temp->mutex->add);
		temp->mutex->time_to_die--;
		pthread_mutex_unlock(&temp->mutex->add);
		temp = temp->next;
	}
	gettimeofday(&time_end, NULL);
	num = calculo(time_start, time_end);
	return (num);
}

int	no_time_philosophers(t_geral **geral)
{
	t_geral			*temp;
	struct timeval	time_start;
	struct timeval	time_end;
	long int		num;

	temp = *geral;
	time_start = temp->mutex->time_start;
	while (temp != NULL)
	{
		if (temp->mutex->end && temp->mutex->time_to_die < 0)
			return (1);
		if (temp->mutex->time_to_die < 0)
		{
			morreu_philosopher(temp->mutex, time_start);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	*life_philosopher(void *arg)
{
	t_geral			**temp;
	long int		num ;
	struct timeval	time_start;
	long int		start_teste;
	long int		end_teste;

	gettimeofday(&time_start, NULL);
	temp = (t_geral **)(arg);
	while (1)
	{
		start_teste = get_time();
		less_time_philosophers(temp);
		if (no_time_philosophers(temp))
			break ;
		end_teste = get_time();
		num = end_teste - start_teste;
		ft_usleep(1);
	}
}

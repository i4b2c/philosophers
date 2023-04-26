/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:25 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void create_lista(t_geral **geral, int num,char **av,int ac)
{
	int i;
	t_geral *temp;
	t_geral *ultimo;
	t_mutex *mutex;
	pthread_mutex_t *die_mutex;
	pthread_mutex_t *print;

	die_mutex = malloc(sizeof(pthread_mutex_t));
	print = malloc(sizeof(pthread_mutex_t));

	ultimo = NULL;
	i = 1;
	pthread_mutex_init(die_mutex,NULL);
	pthread_mutex_init(print,NULL);
	while(i <= num)
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		if(!(i % 2))
			temp->mutex->id_s = 0;
		else
			temp->mutex->id_s = 1;
		temp->mutex->max = ft_atoi(av[1]);
		temp->mutex->time_to_die = ft_atoi(av[2]);
		temp->mutex->time_to_die_reset = ft_atoi(av[2]);
		temp->mutex->time_to_eat = ft_atoi(av[3]);
		temp->mutex->time_to_sleep = ft_atoi(av[4]);
		temp->mutex->time_to_think = ft_atoi(av[2])-ft_atoi(av[3])-ft_atoi(av[4]);
		if(ac == 6)
			temp->mutex->eat_times_max = ft_atoi(av[5]);
		temp->mutex->eat_times = 0;
		temp->mutex->id_philosopher = i;
		iniciar_mutex(temp);
		if(i == 1)
			mutex = temp->mutex;
		temp->mutex->first_mutex = mutex;
		temp->next = NULL;
		temp->mutex->die_mutex = die_mutex;
		temp->mutex->print = print;
		adicionar_na_lista(geral,temp,&ultimo);
		i++;
	}
}

void create_threads(t_geral **geral)
{
	t_geral *temp_geral;

	temp_geral = *geral;
	while(temp_geral != NULL)
	{
		pthread_create(&(temp_geral->mutex->thread),NULL
			,&philosopher,temp_geral);
		temp_geral = temp_geral->next;
	}
}

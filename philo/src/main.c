/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:13 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int ac, char **av)
{
	t_geral		*geral;
	pthread_t	life;

	geral = NULL;
	if (ac != 5 && ac != 6)
		exit_erro();
	create_lista(&geral, 1, av, ac);
	pthread_create(&life, NULL,
		&life_philosopher, &geral);
	create_threads(&geral);
	pthread_join(life, NULL);
	join_threads(&geral, &life);
	destroy_all_mutex(&geral);
	close_everything(&geral);
	return (0);
}

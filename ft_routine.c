/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:29:13 by francesca         #+#    #+#             */
/*   Updated: 2025/04/07 21:36:03 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Prende il tempo attuale (tv_sec, tv_usec)
Converte i secondi in millisecondi → tv_sec * 1000
Converte i microsecondi in millisecondi → tv_usec / 1000
Somma tutto per avere il tempo totale in millisecondi
Ritorna il tempo in millisecondi, per usare nei log.
*/
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000); // piccoli delay per evitare deadlock iniziali

    while (!philo->data->someone_died)
    {
        take_forks(philo);
        eat(philo);
        drop_forks(philo);

        if (philo->data->meals_required != -1 &&
            philo->meals_eaten >= philo->data->meals_required)
            break;

        sleep_and_think(philo);
    }
    return (NULL);
}
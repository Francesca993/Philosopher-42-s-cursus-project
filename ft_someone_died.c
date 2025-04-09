/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_someone_died.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:56:48 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 10:03:22 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    long now;

    while(!data->someone_died)
    {
        i = 0;
        while ( i < data->number_of_philos)
        {
            now = get_time();
            pthread_mutex_lock(&data->print_mutex);
            if ((now - data->philos->last_meal_time) > data->time_to_die)
            {
                data->someone_died = 1;
                printf("%ld %d died\n", now - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->print_mutex);
            i++;
        }
        usleep(1000); // controllo ogni millisecondo
    }
    return (NULL);
}


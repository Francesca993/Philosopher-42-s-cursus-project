/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:56:48 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 12:18:15 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int count_eat(t_data *data)
{
    int i;
    int full_count;
    
    full_count = 0;
    if (data->meals_required == -1)
        return (0);
    i = 0;
    while (i < data->number_of_philos)
    {
        if(data->philos[i].meals_eaten == data->meals_required)
            full_count++;
        i++;
    }
    if (full_count == data->number_of_philos)
    {
        data->all_ate = 1;
        return (1);
    }
    return (0);
}

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
            if ((now - data->philos[i].last_meal_time) > data->time_to_die)
            {
                data->someone_died = 1;
                printf("%ld %d died\n", now - data->start_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->print_mutex);
            i++;
        }
        if (count_eat(data))
            return (NULL);
        usleep(1000); // controllo ogni millisecondo
    }
    return (NULL);
}


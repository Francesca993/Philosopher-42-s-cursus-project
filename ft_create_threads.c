/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:50:56 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 12:16:24 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int create_threads(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time();//per salvare l'inizio della simulazione
    while (i < data->number_of_philos)
    {
        data->philos[i].last_meal_time = data->start_time;
        if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
        {
            printf("Error during creation thread number %d.\n", i + 1);
            return (1);
        }
        i++;
    }
    if (pthread_create(&data->monitor_thread, NULL, &monitor_routine, data) != 0)
    {
        printf("Error creating monitor thread.\n");
        return (1);
    }
    return (0);
}

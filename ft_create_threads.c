/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:50:56 by francesca         #+#    #+#             */
/*   Updated: 2025/04/07 15:29:35 by francesca        ###   ########.fr       */
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
    return (0);
}
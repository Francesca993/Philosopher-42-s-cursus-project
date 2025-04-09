/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:13:15 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 10:18:42 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void join_threads(t_data *data)
{
    int i;
    pthread_join(data->monitor_thread, NULL);
    i = 0;
    while (i < data->number_of_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}
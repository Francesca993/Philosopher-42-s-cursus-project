/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:45:21 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 10:16:48 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_data data;
    
    if ((argc != 5) && (argc != 6))
    {
        printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [meals_each]\n");
        return (1);
    }
    // 2. Parsing e inizializzazione
    if (init_data(&data, argc, argv) != 0)
    {
        printf("Error during inizialization data.\n");
        free_all(&data);
        return (1);
    }
    if (create_threads(&data) != 0)
    {
        free_all(&data);
        return (1);
    }
    // 🧵 Aspetta la fine dei thread
	join_threads(&data);
	// 🧹 Pulisce tutto
	free_all(&data);
    return (0);
}

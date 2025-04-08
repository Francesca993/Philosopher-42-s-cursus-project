/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:55:25 by francesca         #+#    #+#             */
/*   Updated: 2025/04/07 14:45:38 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void ft_init_mutex(t_data *data)
{
    int i;
    
    i = 0;
    while ( i < data->number_of_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

static int check_values(t_data *data, int argc)
{
    if (data->number_of_philos < 1 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0 || ((argc == 6) && data->meals_required <= 0))
        return (1);
    return (0);
}

void    init_philos(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->number_of_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = (&data->forks[(i + 1) % data->number_of_philos]);
        data->philos[i].data = data;
        i++;
    }
}

/*Questa funzione si occupa di fare il parsing (leggere dalla riga di 
terminale).
Farà 4 cose: 
Controlla che tutti gli argomenti siano validi
Converte gli argomenti da *char a int
Riempe la struct con i valori
Alloca memoria per forchette e filosofi, e inizializza i mutex.
*/
int init_data(t_data *data, int argc, char **argv)
{
    data->number_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->meals_required = ft_atoi(argv[5]);
    else
        data->meals_required = -1;
    data->someone_died = 0;
    data->start_time = 0;
    if (check_values(data, argc) == 1)
        return (1);
    //Alloca forchette
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
    if (!data->forks)
        return (1);
    //inizializza i mutex delle forchette
    ft_init_mutex(data);
    //inizializza mutex della stampa
    pthread_mutex_init(&data->print_mutex, NULL);
    //alloca i filosofi
    data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
    if(!data->philos)
        return (1);
    init_philos(data);
    return (0);
}


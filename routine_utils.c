/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:00:02 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 12:03:24 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_status(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died)
        printf("%ld, %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void take_forks(t_philo *philo)
{
     // Lock ordine sinistra-destra o destra-sinistra per evitare deadlock
     if (philo->id % 2 == 0)
     {
         pthread_mutex_lock(philo->right_fork);
         print_status(philo, "has taken a right fork");
         pthread_mutex_lock(philo->left_fork);
         print_status(philo, "has taken a left fork");
     }
     else
     {
         pthread_mutex_lock(philo->left_fork);
         print_status(philo, "has taken a left fork");
         pthread_mutex_lock(philo->right_fork);
         print_status(philo, "has taken a right fork");
     }
}

void    drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->data->print_mutex);

    print_status(philo, "is eating");
    philo->meals_eaten++;
    usleep(philo->data->time_to_eat * 1000);
}

void sleep_and_think(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    print_status(philo, "is thinking");
}
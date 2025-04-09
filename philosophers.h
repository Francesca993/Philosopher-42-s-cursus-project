/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:27:49 by francesca         #+#    #+#             */
/*   Updated: 2025/04/09 12:12:35 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
#include <stdio.h>         // printf
#include <stdlib.h>        // malloc, free, atoi
#include <unistd.h>        // usleep
#include <pthread.h>       // pthreads e mutex
#include <sys/time.h>      // gettimeofday per timestamp

// ---------- Struct ---------- //

typedef struct s_philo t_philo;

//Tutto quello che deve essere visibile a tutti i filosofi vive dentro t_data.
//Tutto il resto: tempo, forchette, mutex, filosofi
typedef struct s_data {
	int             number_of_philos;   // Numero totale di filosofi
	int        		time_to_die;        // Tempo massimo prima di morire senza mangiare (ms)
	int             time_to_eat;        // Durata del pasto (ms)
	int             time_to_sleep;      // Durata del sonno (ms)
	int             meals_required;     // Quante volte ogni filosofo deve mangiare (opzionale)
	long            start_time;         // Timestamp di inizio simulazione
	int             someone_died;               // Flag: qualcuno è morto? (1 sì, 0 no)
	int				all_ate;
	pthread_mutex_t *forks;             // Array di mutex per le forchette
	pthread_mutex_t print_mutex;        // Mutex per stampare i log senza overlap
	pthread_t monitor_thread;           // thread per monitorare la morte dei filosofi
	t_philo         *philos;            // Array di filosofi
} t_data;


//Ogni filosofo ha le sue info private, ma condivide i dati globali tramite *data.
//Dati di un singolo filosofo: ID, thread, stato
typedef struct s_philo {
	int             id;                 // ID del filosofo (da 1 a N)
	int             meals_eaten;        // Conteggio dei pasti (se richiesto)
	long            last_meal_time;     // Timestamp dell’ultimo pasto (per evitare la morte)
	pthread_t       thread;             // Thread associato al filosofo
	struct s_data   *data;              // Puntatore ai dati condivisi (accesso a forks, timer, ecc)
	pthread_mutex_t *left_fork;         // Puntatore al mutex della forchetta sinistra
	pthread_mutex_t *right_fork;        // Puntatore al mutex della forchetta destra
} t_philo;
//Utils function
int		ft_atoi(const char *str);
void	free_all(t_data *data);
//Function to initizialize the struct and parsing
int		init_data(t_data *data, int argc, char **argv);
void    init_philos(t_data *data);
int		create_threads(t_data *data);
long	get_time(void);
//Function for routine
void	*routine(void *arg);
void    print_status(t_philo *philo, char *msg);
void	take_forks(t_philo *philo);
void    drop_forks(t_philo *philo);
void    eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void    *monitor_routine(void *arg);
void	join_threads(t_data *data);

#endif
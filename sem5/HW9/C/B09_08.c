#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>
#include <time.h>

#define NUM_CLIENTS 10

size_t served_in_time = 0;

struct serving_data 
{
    size_t thread_idx;

    double arrive_time;
    double waiting_time;
    double waiting_threshold;

    sem_t *lock;
};


struct timespec create_timespec(double secs)
{
    int seconds = (int) secs;
    long nanoseconds = (secs - seconds) * 1e9;
    struct timespec ts = {
        .tv_sec = seconds,
        .tv_nsec = nanoseconds
    };

    return ts;
}


void *serve_client(void *arg)
{
    struct serving_data *data = arg;
    struct timespec arrive_time = create_timespec(data->arrive_time);
    struct timespec waiting_time = create_timespec(data->waiting_time);
    double waiting_threshold = data->waiting_threshold;
    size_t thread_idx = data->thread_idx;

    sem_t *lock = data->lock;

    time_t start, end;

    nanosleep(&arrive_time, NULL);
    printf("Customer %zu arrived at the restaurant\n", thread_idx);
    start = time(NULL);

    sem_wait(lock);

    nanosleep(&waiting_time, NULL); /* Getting served */

    sem_post(lock);

    end = time(NULL);
    printf("Customer %zu has been served\n", thread_idx);

    served_in_time += difftime(end, start) > waiting_threshold ? 0 : 1;

    return arg;
}

int main(void)
{
    int N = 5;  /* Cook count */
    int M = 10; /* Client count */
    double T1 = 1.000;
    double T2 = 2.000;
    double T3 = 3.000;
    double T4 = 4.000;
    double T5 = 3.500;
    
    sem_t *lock = NULL;
    lock = sem_open("/cook_semaphore", O_CREAT | O_EXCL, 0, N); 

    srand(time(NULL));

    pthread_t *threads = malloc(M * sizeof(pthread_t));

    struct serving_data *datas = malloc(M * sizeof(struct serving_data));

    for (size_t i = 1; i <= M; i++){

        double rand_coef1 = (double) rand() / (double) RAND_MAX;
        double rand_coef2 = (double) rand() / (double) RAND_MAX;
        
        datas[i] = (struct serving_data){
           .thread_idx = i,
           .arrive_time = ((T2-T1) * rand_coef1) + T1,
           .waiting_time = ((T4-T3) * rand_coef2) + T2,
           .waiting_threshold = T5,
           .lock = lock
        };

        pthread_create(&threads[i-1], NULL, serve_client, &datas[i]);
    }


    for (size_t i = 0; i < M; i++)
        pthread_join(threads[i], NULL);

    printf("Overall served in time were %zu people\n", served_in_time);


    sem_unlink("/cook_semaphore");
    free(threads);

    return 0; 
}



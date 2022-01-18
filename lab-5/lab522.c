#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct itimerspec timer1_time;
timer_t timer1;

void timestamp(char *str){
    time_t t;
    time(&t);
    printf("The time %s is %s\n", str, ctime(&t));
}

void initialize_periodic_timer(long period){
    if(timer_create(CLOCK_REALTIME, NULL, &timer1) != 0 ){
        perror("timer_create");
        exit(1);
    }
    timer1_time.it_value.tv_sec = 3;
    timer1_time.it_value.tv_nsec = 0;
    timer1_time.it_interval.tv_sec = 0;
    timer1_time.it_interval.tv_nsec = period * 1000000; //500000000 = 0.5s
    if(timer_settime(timer1, 0, &timer1_time, NULL) != 0 ){
        perror("timer_settime");
        exit(1);
    }
}

// handle deadline miss
static void deadline_missed(){
    printf("error: deadline missed!\n");
}

void handle_deadline_missed(void){
    struct sigaction act;
    act.sa_handler = &deadline_missed;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);
}

int main(int argc, char *argv[]){

    struct sched_param spar;
    int priority = atoll(argv[2]);
    char *policy = argv[4];
    int sched_policy;
    if(strcmp(policy, "SCHED_FIFO") == 0){
        sched_policy = SCHED_FIFO;
        printf("SCHED_FIFO is used!\n");
    }
    else if(strcmp(policy, "SCHED_RR") == 0){
        sched_policy = SCHED_RR;
        printf("SCHED_RR is used!\n");
    }
    else{
        printf("scheduling policy error!");
        exit(1);
    }
    spar.sched_priority = sched_get_priority_min(sched_policy) + priority;
    sched_setscheduler(0, sched_policy, &spar);

    sigset_t waiting_signals;
    sigemptyset(&waiting_signals);
    sigaddset(&waiting_signals, SIGALRM);

    handle_deadline_missed();

    long period = atoll(argv[1]);
    initialize_periodic_timer(period);

    while(1){
        int received_signal;
        // sleep() provokes a deadline miss
        // sleep(5);
        sigwait(&waiting_signals, &received_signal);
        int load = atoll(argv[3]);
        timer_gettime(timer1, &timer1_time);
        for(int i=0; i<load*1000;i++){}
        printf("With %d load, the execution time of empty loop is: %ld nanoseconds\n", 
            load, period * 1000000 - timer1_time.it_value.tv_nsec);
        // printf("A new period ends!\n");
    }
    return 0; // never reach here
}

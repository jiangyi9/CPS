#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void initialize_periodic_timer(){
    struct itimerspec timer1_time;
    timer_t timer1;
    if(timer_create(CLOCK_REALTIME, NULL, &timer1) != 0 ){
        perror("timer_create");
        exit(1);
    }
    timer1_time.it_value.tv_sec = 3;
    timer1_time.it_value.tv_nsec = 0;
    timer1_time.it_interval.tv_sec = 1;
    timer1_time.it_interval.tv_nsec = 0; //500000000 = 0.5s
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

int main(){
    sigset_t waiting_signals;
    sigemptyset(&waiting_signals);
    sigaddset(&waiting_signals, SIGALRM);

    handle_deadline_missed();

    initialize_periodic_timer();

    while(1){
        int received_signal;
        // sleep() provokes a deadline miss
        sleep(5);
        sigwait(&waiting_signals, &received_signal);
        printf("A new period ends!\n");
    }
    return 0; // never reach here
}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ev.h>

ev_timer time_watcher;
ev_io io_watcher;

int ms=0,s=0;
static void io_cb(EV_P_ ev_io *w, int revents){
    puts("stop");
	// for one-shot events, one must manually stop the watcher
	// with its corresponding stop function.
	ev_io_stop(loop, w);
	// this causes all nested ev_run's to stop iterating
	ev_break(loop, EVBREAK_ALL);
    // ev_sleep(1);
}
static void timer_cb(EV_P_ ev_timer *w, int revents){
    if(ms/100!=0){
        s++;
        ms=0;
    }
    printf("%d.%02d",s,ms);
    system("clear");
    fflush(stdout);
    ms++;
}

void main(){
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init(&io_watcher,io_cb,0,EV_READ);
    ev_io_start(loop, &io_watcher);
    ev_timer_init(&time_watcher,timer_cb,0,0.1);
    ev_timer_start(loop, &time_watcher);
    ev_run(loop, 0);
    
    // ev_io_init(&io_watcher,io_cb,0,EV_READ);
    // ev_io_set(&io_watcher,0,EV_READ);
    // ev_io_start(loop, &io_watcher);
    // ev_timer_init(&time_watcer,timer_cb,0,0.1);
    // ev_timer_set(&time_watcer,0,0.1);
    // ev_timer_start(loop, &time_watcer);
    // ev_run(loop,0);
}
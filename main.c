#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ev.h>

ev_timer time_watcher;
ev_io io_watcher;

int s=0;
static void io_cb(EV_P_ ev_io *w, int revents){
    puts("stop");
    getchar(); //把\n吃掉以繼續監看io
	// for one-shot events, one must manually stop the watcher
	// with its corresponding stop function.
	ev_io_stop(loop, w);
    /* ev_timer_stop的必要性？*/
    ev_timer_stop(loop,&time_watcher);
	// this causes all nested ev_run's to stop iterating
	ev_break(loop, EVBREAK_ALL);
}
static void timer_cb(EV_P_ ev_timer *w, int revents){
    
    printf("%d",s);
    system("clear");
    fflush(stdout);
    s++;
}

void main(){
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init(&io_watcher,io_cb,0,EV_READ);
    ev_io_start(loop, &io_watcher);
    ev_timer_init(&time_watcher,timer_cb,0,1);
    ev_timer_start(loop, &time_watcher);
    ev_run(loop, 0);
    while(1){
        
        ev_io_init(&io_watcher,io_cb,0,EV_READ);
        // ev_io_set(&io_watcher,0,EV_READ);
        ev_io_start(loop, &io_watcher);
        // ev_timer_init(&time_watcer,timer_cb,0,0.1);
        // ev_timer_set(&time_watcher,0,0.1);
        ev_timer_init(&time_watcher,timer_cb,0,1);
        ev_timer_again(loop,&time_watcher);
        ev_run(loop,0);
    }
}
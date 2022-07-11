#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, 
struct RCB new_request, int timestamp);

struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt);

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, 
struct RCB new_request, int timestamp);

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder);

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, 
struct RCB new_request, int timestamp);

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int  *queue_cnt, int current_cylinder, int scan_direction);

struct RCB NULLRCB();


struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, 
struct RCB new_request, int timestamp) {
    struct RCB nullrcb = NULLRCB(); //Inititialize the nullrcb
    //If current process is nullrcb, return new request
    if(current_request.process_id == 0) {
        return new_request;
    } else {
        (*queue_cnt)++; //Add 1 to queue count to prepare queue for new addition
        //Add new request to the request queue
        for(int i = *queue_cnt-1; i < *queue_cnt; i++) {
            request_queue[i].request_id = new_request.request_id;
            request_queue[i].arrival_timestamp = new_request.arrival_timestamp;
            request_queue[i].cylinder = new_request.cylinder;
            request_queue[i].address = new_request.address;
            request_queue[i].process_id = new_request.process_id;
        }
        return current_request;
    }
}

struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt) {
    struct RCB nullrcb = NULLRCB(); //Inititialize the nullrcb
    struct RCB returnRCB;
    int selection = 0;
    //If queue is empty, return nullrcb
    if(*queue_cnt == 0) {
        return nullrcb;
    } else {
        //Select the rcb with the lowest arrival time from the request queue
        for(int i = 0; i < *queue_cnt; i++) {
            if(request_queue[i].arrival_timestamp < request_queue[selection].arrival_timestamp) {
                selection = i;
            }
        }
        returnRCB = request_queue[selection];
        //Remove return_PCB process from ready_queue and update queue_cnt
        for(int i = selection; i < *queue_cnt; i++) {
            request_queue[i] = request_queue[i+1];
        }
        (*queue_cnt)--;
        return returnRCB;
    }
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, 
struct RCB new_request, int timestamp) {
    struct RCB nullrcb = NULLRCB(); //Inititialize the nullrcb
    //If current process is nullrcb, return new request
    if(current_request.process_id == 0) {
        return new_request;
    } else {
        (*queue_cnt)++; //Add 1 to queue count to prepare queue for new addition
        //Add new request to the request queue
        for(int i = *queue_cnt-1; i < *queue_cnt; i++) {
            request_queue[i].request_id = new_request.request_id;
            request_queue[i].arrival_timestamp = new_request.arrival_timestamp;
            request_queue[i].cylinder = new_request.cylinder;
            request_queue[i].address = new_request.address;
            request_queue[i].process_id = new_request.process_id;
        }
        return current_request;
    }
}

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder) {
    struct RCB nullrcb = NULLRCB(); //Inititialize the nullrcb
    struct RCB returnRCB;
    int selection = 0;
    //If queue is empty, return nullrcb
    if(*queue_cnt == 0) {
        return nullrcb;
    } else {
        //Select the rcb with that most closley matches current cylinder
        for(int i = 0; i < *queue_cnt; i++) {
            if(abs(request_queue[i].cylinder - current_cylinder) < abs(request_queue[selection].cylinder - current_cylinder)) {
                selection = i;
            }
        }
        returnRCB = request_queue[selection]; //Save selection to returnRCB;
        //Remove return_PCB process from ready_queue and update queue_cnt
        for(int i = selection; i < *queue_cnt; i++) {
            request_queue[i] = request_queue[i+1];
        }
        (*queue_cnt)--;
        return returnRCB;
    }
}

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, 
struct RCB new_request, int timestamp) {
    struct RCB nullrcb = NULLRCB(); //Inititialize the nullrcb
    //If current process is nullrcb, return new request
    if(current_request.process_id == 0) {
        return new_request;
    } else {
        (*queue_cnt)++; //Add 1 to queue count to prepare queue for new addition
        //Add new request to the request queue
        for(int i = *queue_cnt-1; i < *queue_cnt; i++) {
            request_queue[i].request_id = new_request.request_id;
            request_queue[i].arrival_timestamp = new_request.arrival_timestamp;
            request_queue[i].cylinder = new_request.cylinder;
            request_queue[i].address = new_request.address;
            request_queue[i].process_id = new_request.process_id;
        }
        return current_request;
    }
}

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int  *queue_cnt, int current_cylinder, int scan_direction) {
    struct RCB nullrcb = NULLRCB(); //Inititialize the nullrcb
    struct RCB returnRCB;
    int large_small_bits[QUEUEMAX];
    int selection = 0; //Keeps track of selected RCB
    int larger = 0; //Keeps track of if there are cylinders larger than current cylinder in the queue
    int smaller = 0; //Keeps track of if there are cylinders smaller than current cylinder in the queue
    for(int i = 0; i < *queue_cnt; i++) {
        if(request_queue[i].cylinder > current_cylinder) {
            larger = 1;
            large_small_bits[i] = 1;
        } else if (request_queue[i].cylinder < current_cylinder) {
            smaller = 1;
            large_small_bits[i] = 0;
        } else {
            large_small_bits[i] = 2;
        }
    }
    if(larger) {
        for(int i = 0; i < *queue_cnt; i++) {
            if(large_small_bits[i] == 1) {
                selection = i;
            }
            break;
        }
    } else if(smaller) {
        for(int i = 0; i < *queue_cnt; i++) {
            if(large_small_bits[i] == 0) {
                selection = i;
            }
            break;
        }
    } else {
        for(int i = 0; i < *queue_cnt; i++) {
            if(large_small_bits[i] == 2) {
                selection = i;
            }
            break;
        }
    }
    //If request queue is empty, return nullrcb
    if(*queue_cnt == 0) {
        return nullrcb;
    } else {
        for(int i = 0; i < *queue_cnt; i++) {
            if(request_queue[i].cylinder == current_cylinder && 
            request_queue[i].arrival_timestamp < request_queue[selection].arrival_timestamp) {
                selection = i;
            } else if (scan_direction == 1) {
                if(larger) {
                    if(large_small_bits[i] == 1 && 
                    abs(request_queue[i].cylinder - current_cylinder) < abs(request_queue[selection].cylinder - current_cylinder)) {
                        selection = i;
                    }
                } else {
                    if(abs(request_queue[i].cylinder - current_cylinder) < abs(request_queue[selection].cylinder - current_cylinder)) {
                        selection = i;
                    }
                }
            } else if (scan_direction == 0) {
                if(smaller) {
                    if(large_small_bits[i] == 0 && 
                    abs(request_queue[i].cylinder - current_cylinder) < abs(request_queue[selection].cylinder - current_cylinder)) {
                        selection = i;
                    }
                } else {
                    if(abs(request_queue[i].cylinder - current_cylinder) < abs(request_queue[selection].cylinder - current_cylinder)) {
                        selection = i;
                    }
                }
            }
        }
        returnRCB = request_queue[selection]; //Save selection to returnRCB;
        //Remove return_PCB process from ready_queue and update queue_cnt
        for(int i = selection; i < *queue_cnt; i++) {
            request_queue[i] = request_queue[i+1];
        }
        (*queue_cnt)--;
        return returnRCB;
    }
}

//Function used to initialize NULLPCB
struct RCB NULLRCB() {
    struct RCB nullrcb;
    nullrcb.request_id = 0;
    nullrcb.arrival_timestamp = 0;
    nullrcb.cylinder = 0;
    nullrcb.address = 0;
    nullrcb.process_id = 0;
    return nullrcb;
};

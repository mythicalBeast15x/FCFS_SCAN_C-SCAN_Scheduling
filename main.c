#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CYLINDERS 5000
int FCFS_Scheduling(int *cylinders, int *requests, int requestNum, int head){
    int headMovement = 0;
    for(int x = 0; x < requestNum; x++){
        while(head !=requests[x]){
            if(head < requests[x]){
                head++;
            }else{
                head--;
            }
            headMovement++;
        }
        cylinders[head] = 1;
    }
    //printf("FCFS done\n");
    return headMovement;
}
int SCAN_Scheduling(int *cylinders, int *requests, int requestNum, int head){
    int headMovement = 0;
    int sortedRequests[requestNum];
    int counter = 0;
    int nextIndex = -1;
    int headResetIndex;
    while (counter < requestNum) {
        int lowest = 5001; // Initialize to a large value
        int resetIndex = -1; // Initialize to an invalid index
        for (int x = 0; x < requestNum; x++) {
            if (requests[x] != -1) {
                if (requests[x] < lowest) {
                    lowest = requests[x];
                    resetIndex = x;
                }
            }
        }
        sortedRequests[counter] = lowest;
        if (head < lowest && nextIndex == -1) {
            nextIndex = counter-1;
            headResetIndex = head;
        }
        requests[resetIndex] = -1;
        counter++;
    }
    /*printf("%d\n", counter);
    for(int x = 0; x < requestNum; x++){
        printf("%d,%d\n", sortedRequests[x], requests[x]);
    }*/
    //printf("%d, %d, %d, %d\n", headResetIndex, sortedRequests[headResetIndex], nextIndex, sortedRequests[nextIndex]);
    //go to left end
    while(head > 0){
        //get next index
        //loop until next index
        //etc
        //printf("%d -> %d\n", head, sortedRequests[nextIndex]);
        while(head > sortedRequests[nextIndex]){
            head--;
            headMovement++;
        }
        cylinders[head] = -2;
        nextIndex--;
    }
    nextIndex = headResetIndex;
    while(head < sortedRequests[requestNum-1]){
        //get next index
        //loop until next index
        //etc
        while(head < sortedRequests[nextIndex]){
            head++;
            headMovement++;
        }
        cylinders[head] = -2;
        nextIndex++;
    }
    // go to right end

/*
    printf("%d,%d",sortedRequests[0],sortedRequests[999]);
    for(int x = 0; x < 5000; x++){
        printf("%d\n", cylinders[x]);
    }
*/
    //printf("SCAN done\n");
    return headMovement;
}
int C_SCAN_Scheduling(int *cylinders, int *requests, int requestNum, int head){
    int headMovement = 0;
    int sortedRequests[requestNum];
    int counter = 0;
    int nextIndex = -1;
    int servicedCounter = 0;
    int headResetIndex;
    //
    while (counter < requestNum) {
        int lowest = 5001; // Initialize to a large value
        int resetIndex = -1; // Initialize to an invalid index
        for (int x = 0; x < requestNum; x++) {
            if (requests[x] != -1) {
                if (requests[x] < lowest) {
                    lowest = requests[x];
                    resetIndex = x;
                }
            }
        }
        sortedRequests[counter] = lowest;
        if (head < lowest && nextIndex == -1) {
            nextIndex = counter;
        }
        requests[resetIndex] = -1;
        counter++;
    }
    //printf("%d\n", counter);
    /*
    for(int x = 0; x < requestNum; x++){
        printf("%d,%d\n", sortedRequests[x], requests[x]);
    }*/
    //now sorted
    //printf("now sorted \n");
    while(servicedCounter < requestNum){
        while(head < sortedRequests[nextIndex]){
            head++;
            headMovement++;
        }
        cylinders[head] = -3;
        servicedCounter++;
        if(head == sortedRequests[requestNum-1]){
            head = 0;
            nextIndex = 0;
            //printf("Reset\n");
        }
        nextIndex++;
    }
    //printf("CSCAN done\n");
    return headMovement;
}

int main(int argc, char *argv[]) {
    //assign head
    int head = 0;
    if(argc < 2){
        //get input
        printf("Enter Head Position:");
        scanf("%d", &head);
        if(head < 0 || head > 5000){
            printf("Invalid Head Position\nSetting Head to 53\n");
            head = 53;
        }
    } else{
        head = atoi(argv[1]);
    }
    srand(time(NULL));
    //initialize list
    int requestNum = 1000;
    int cylinders[MAX_CYLINDERS];
    int cylinders2[MAX_CYLINDERS];
    int cylinders3[MAX_CYLINDERS];
    int requests[requestNum];
    int requests2[requestNum];
    int requests3[requestNum];
    for(int c = 0; c < MAX_CYLINDERS; c++){
        cylinders[c] = 0;
        cylinders2[c] = 0;
        cylinders3[c] = 0;
    }
    for(int c = 0; c < requestNum; c++){
        requests[c] = rand() % (MAX_CYLINDERS);
        int x = 0;
        while(x < c){
             if(requests[x] == requests[c]){
                 //printf("%d : %d\n",requests[c], requests[x]);
                 requests[c] = rand() % (MAX_CYLINDERS);

                 x = 0;
             }else{
                 x++;
             }

        }
        requests2[c] = requests[c];
        requests3[c] = requests[c];
        //printf("%d\n", requests[c]);
    }

    int fcfs = FCFS_Scheduling(cylinders, requests, 1000, head);
    int scan = SCAN_Scheduling(cylinders2, requests2, 1000, head);
    int cscan = C_SCAN_Scheduling(cylinders3, requests3, 1000, head);
    printf("FCFS: %d\nSCAN: %d\nC-SCAN: %d", fcfs,scan,cscan);
    return 0;
}

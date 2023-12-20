//
// Created by franzozich on 20/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "segdef.h"

#define segsize sizeof(segment)

void init_rand(){
    srand(time(NULL));
}
long getrand() {
    return (long)rand() << 15 | rand();
}

void wait_sem(int sem_id, int num_sem) {
    struct sembuf op;

    op.sem_num = num_sem;
    op.sem_op = -1;
    op.sem_flg = 0;
    if (semop(sem_id, &op, 1) == -1) {
        perror("semop wait");
        exit(1);
    }
}

void acq_sem(int sem_id, int num_sem) {
    struct sembuf op;

    op.sem_num = num_sem;
    op.sem_op = -1;
    op.sem_flg = 0;
    if (semop(sem_id, &op, 1) == -1) {
        perror("semop signal");
        exit(1);
    }
}

void lib_sem(int sem_id, int num_sem) {

    struct sembuf operations[1];

    operations[0].sem_num = num_sem;
    operations[0].sem_op = 1;
    operations[0].sem_flg = 0;

    if (semop(sem_id, operations, 1) == -1) {
        perror("semop - lib_sem");
        exit(1);
    }

}



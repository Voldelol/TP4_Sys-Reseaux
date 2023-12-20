#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "segdef.h"

int main() {
    int semdispo,seminit,semres, shmid;
    segment *shmptr;

    if ((semdispo = semget(cle, seg_dispo, 0)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    if ((seminit = semget(cle, seg_init, 0)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    if ((semres = semget(cle, res_ok, 0)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    if ((shmid = shmget(cle, segsize, 0)) == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if ((shmptr = (segment*)shmat(shmid, NULL, 0)) == (void*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    init_rand();
    int req=0;
    while (1) {
        long long moy=0;
        acq_sem(semdispo, seg_dispo);

        shmptr->pid = getpid();
        shmptr->req = ++req;
        for (int i = 0; i < maxval; ++i) {
            shmptr->tab[i] = getrand();
            moy+=shmptr->tab[i];
        }
        moy=moy/maxval;
        acq_sem(seminit,seg_init);


        wait_sem(semres,res_ok);


        printf("Received result: %ld\n", shmptr->result);
        printf("Local result: %ld\n", moy);
        if(shmptr->result==moy){
            printf("GG\n");
        }
        lib_sem(seminit,seg_init);
        acq_sem(semres, res_ok);
        lib_sem(semres, res_ok);

        lib_sem(semdispo, seg_dispo);

        sleep(2);
    }


    return 0;
}


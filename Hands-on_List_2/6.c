/***************************************************************************************************
 *Name: 6.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a simple program to create three threads
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_run(void *arg) {
  printf("Thread %ld is running \n",(long)arg);
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[3];
  for (int i = 0 ; i < 3; i++ ) {
    if ( pthread_create(&threads[i],NULL,thread_run,(void*)(long)i) != 0) {
      perror("Thread creation failed!");
      exit(EXIT_FAILURE);
    }
    printf("Created Thread %d\n",i);
  }
  
  //waiting for the threads to finish
  for (int i = 0; i < 3; i++) {
    if (pthread_join(threads[i],NULL) != 0) {
      perror("Thread join failed!");
      exit(EXIT_FAILURE);
    }
    printf("Thread %d finished\n",i);
  }   
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Created Thread 0
Created Thread 1
Created Thread 2
Thread 0 is running 
Thread 1 is running 
Thread 0 finished
Thread 1 finished
Thread 2 is running 
Thread 2 finished
*/


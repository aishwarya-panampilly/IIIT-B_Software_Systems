/***************************************************************************************************
 *Name: 7.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a simple program to print the created thread ids
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread_function(void *arg) {
  pthread_t thread_id = pthread_self();
  printf("Thread ID: %lu\n",(unsigned long)thread_id);
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[3];
  int i;
  
  for (i = 0; i < 3; i++) {
    if(pthread_create(&threads[i],NULL,thread_function,NULL) != 0) {
      perror("Thread creation failed!");
      exit(EXIT_FAILURE);
    }
    printf("Created thread ID: %lu\n", (unsigned long)threads[i]);
  }
  
  //wait for the threads complete
  for (i = 0; i < 3;i++) {
    if (pthread_join(threads[i],NULL) != 0) {
      perror("Thread join failed!");
      exit(EXIT_FAILURE);
    }
    printf("Thread ID %lu finished\n",(unsigned long)threads[i]);
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Created thread ID: 128813633636032
Thread ID: 128813633636032
Created thread ID: 128813623150272
Thread ID: 128813623150272
Created thread ID: 128813612664512
Thread ID: 128813612664512
Thread ID 128813633636032 finished
Thread ID 128813623150272 finished
Thread ID 128813612664512 finished
*/


/***************************************************************************************************
 *Name: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Problem Statement : Write a program to display the environmental variable of the user (use environ)
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h> //contains environ
extern char **environ; //it points to an array of pointers to strings. Last pointer has NULL value
int main() 
{
  char **en = environ; 
  printf("Environmental Variables of User\n");
  while (*en) // while the last pointer hasn't been reached yet
  {
    printf("%s\n",*en); //print each string
    en++; //move to next pointer
  }
  return 0;
}

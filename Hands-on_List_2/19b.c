/***************************************************************************************************
 *Name: 19b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Create a FIFO file by
                b. mkfifo command
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
/*
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ mkfifo new_fifo
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ ls -l new_fifo
prw-rw-r-- 1 aishjp aishjp 0 Sep 20 21:37 new_fifo
*/
/******************************************OUTPUT************************************************/
//open two terminals to read and write
/*** Terminal 1 ***/
/*
echo "Hello" > new_fifo
*/
/*** Terminal 2 ***/
/*
cat < new_fifo
Hello
*/



/***************************************************************************************************
 *Name: 19a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Create a FIFO file by
                a. mknod command
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
/*
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ mknod my-fifo p
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ ls -l my-fifo
prw-rw-r-- 1 aishjp aishjp 0 Sep 20 21:00 my-fifo
*/
/******************************************OUTPUT************************************************/
//open two terminals to read and write
/*** Terminal 1 ***/
/*
echo "Hello" > my-fifo
*/
/*** Terminal 2 ***/
/*
cat < my-fifo
Hello
*/

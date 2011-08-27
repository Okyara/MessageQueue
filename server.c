//This file will create a child process and read messageas from the message queue.
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main()
{
	pid_t pid;

	//This file will create a child process which will own exact copy
	//of the parent's descriptors. These descriptors reference the 
	//same underlying objects meaning that we are able to access q_entry
	//created in the parent process initiated by client.c 

	//Initialise a struct of type q_entry which we created in client.c
	struct q_entry msg;

	//Read a message from the queue.
	msg = server();

		switch (pid = fork()) 
		{
			case 0:
				if(msg.mtype%2 == 0)
				{
					printf("This is child, my PID is %i. I am receiving messages with even numbered    						priorities.\nMessage: %s\nPriority: %ld\n", getpid(), msg.mtext,msg.mtype);
				}
				break;
			case -1:
				printf("process: fork() failed\n");
				break;
			default:
				if(msg.mtype%2 > 0)
				{
					printf("This is parent, my PID is %d. I am receiving messages with odd numbered 					priorities.\nMessage: %s\nPriority: %ld\n", getpid(), msg.mtext, msg.mtype);
				}
				break;
		}//switch

	return 0;
}//main



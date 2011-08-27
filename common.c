#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "common.h"
#include <stdlib.h>

#define QKEY	(key_t)0105	// queue identifier
#define QPERM		0660	// queue permissions
#define MAXLENGTH	50	// max. length of objname
#define MAXPRIOR	10	// max. priority level



//================================================================

int enter (char *objname, int priority)
{
	int len;
	int s_qid;
	struct q_entry s_entry;

	// Check message length. 
	if ((len = strlen (objname)) > MAXLENGTH)
	{
		perror("msg: msg length is too long.\n");
		exit(0);
	}
	//Cheak message priority.
	if (priority > MAXPRIOR || priority < 0)
	{
		perror("msg: msg priority is invalid.");
		exit(0);
	}

	//Fill up the message struct.	
	s_entry.mtype = priority;
	
	int i;
	for(i = 0; i < sizeof(objname); i++)
	{
		 s_entry.mtext[i] = objname[i];
	}

	//Initialize/open msg queue.
	if ((s_qid =init_queue()) == -1)
	{
		perror("msg: init_queue() failed.\n");
		exit(0);	
	}

	//Put message on the message queue.
	if (msgsnd(s_qid, &s_entry, len, 0) == -1)
	{
		perror("msg: msgsend() failed.\n");
		exit(0);	
	}
	else return (0);

}//enter


int init_queue(void)
{
	int queue_id;

	if ( (queue_id = msgget(QKEY, IPC_CREAT | QPERM) ) == -1)
	{
		perror("msg: msgget() failed.\n");
		exit(0);
	}

	return (queue_id);
}//init_queue


//Read messages from the queue.
struct q_entry server(void)
{
	int mlen, r_qid;
	struct q_entry r_entry;

	// initialize queue
	if ( ( r_qid = init_queue() ) == -1) 
	{	
		perror("msg: init_queue() failed.\n");
		exit(0);	
	}
	for (;;)
	{
		if (( mlen = msgrcv(r_qid, &r_entry, MAXLENGTH, (-1 * MAXPRIOR), MSG_NOERROR)) == -1)
		{
			perror("msg: msgrcv() failed.\n");
			exit(0);
		}else{
			return r_entry;
		}  
		
	}//for	
}//server

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "common.c"

main (int argc, char **argv)
{
	int index;

	//Loop through the secong argument and test each character whether it is 
	//an integer; exit the program if it is not.
	for(index = 0; index < strlen(argv[2]); index++)
	{
		if(argv[2][index] >= '0' && argv[2][index] <= '9')
		{
			//Convert the second argument to an integr with atoi().
			enter(argv[1], atoi(argv[2]));			
		}
		else 
		{
			printf("msg: The message priority must be an integer value.\n");
			exit(0);
		}
	
	}//for
	exit(0);
}//main

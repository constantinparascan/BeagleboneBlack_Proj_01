#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#include "7_Seg_Display_thread.h"




int main (void)
{

	DISP_7_SEG_msg msg_Rx;
	int msg_queue_ID = 0;
	int nStatus = 0;


	msg_queue_ID = msgget((key_t)DISP_7_SEG_msg_ID_KEY, 0666);

	if(msg_queue_ID < 0)
	{
		printf("\nERROR: Cannot connect to receive queue!");
		exit(1);
	}

	while(1)
	{
		nStatus = msgrcv(msg_queue_ID,
				         (void *)&msg_Rx,
				         DISP_7_SEG_DISP_NUM_CELLS /* sizeof (DISP_7_SEG_msg.DISP_7_Seg_val) */,
						 0, 0);

		if(nStatus < 0)
		{

		}
	}


	return 0;
}

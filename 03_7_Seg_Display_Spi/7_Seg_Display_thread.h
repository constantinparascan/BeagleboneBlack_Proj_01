#ifndef __7_SEG_DISPLAY_THREAD__
#define __7_SEG_DISPLAY_THREAD__

#define DISP_7_SEG_DISP_NUM_CELLS (8)


/*
 * Message Queue identification key
 */

#define DISP_7_SEG_msg_ID_KEY    (27041980)

/*
 * Message queue
 *
 *
 *
 */

typedef struct DISP_7_SEG_msg_structure
{
    long int my_msg_type;

    unsigned char DISP_7_Seg_val[ DISP_7_SEG_DISP_NUM_CELLS ];

}DISP_7_SEG_msg;




#endif /* __7_SEG_DISPLAY_THREAD__ */

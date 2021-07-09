#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#include <chrono>
#include <iostream>
#include <thread>

#define BUFFER_SZ (20)

typedef struct
{
    long int msg_type;
    char text [ BUFFER_SZ ];
} MsgWrapper;

void Receiver( )
{
    MsgWrapper data;
    long int msgtype = 2;
    int msgid = msgget( ( key_t )1024, 0666 | IPC_CREAT );
    if ( msgid == -1 )
    {
        std::cout << "msgget error.\n";
        return;
    }

    while ( true )
    {
        if ( msgrcv( msgid, ( void* )&data, BUFFER_SZ, msgtype, 0 ) == -1 )
        {
            std::cout << "error: " << errno << std::endl;
        }
        std::cout << "read data " << data.text << std::endl;
        if ( strlen( data.text ) > 6 )
        {
            break;
        }
        if ( msgct )
        {
            /* code */
        }

    }
}
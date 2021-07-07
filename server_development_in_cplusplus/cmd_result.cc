#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <memory>

// 通过popen将另一个程序当作一个新的进程在当前进程中启动，它算作当前进程的子进程
// 高级管道可以用在父子进程间进行通信
std::string get_cmd_result( const std::string& cmd, int max_size = 10 )
{
    char* data = ( char* )malloc( max_size );
    if ( data == nullptr )
    {
        return std::string( "malloc fail" );
    }

    memset( data, 0, max_size );
    const int max_buffer = 256;
    char buffer [ max_buffer ];
    FILE* fdp = popen( ( cmd + " 2>&1" ).c_str( ), "r" );
    int data_len = 0;

    if ( fdp )
    {
        while ( !feof( fdp ) )
        {
            if ( fgets( buffer, max_buffer, fdp ) )
            {
                int len = strlen( buffer );
                if ( data_len + len > max_size )
                {
                    std::cout << "data size larger than " << max_size;
                }
                memcpy( data + data_len, buffer, len );
                data_len += len;
            }
        }
        pclose( fdp );
    }
    std::string ret( data, data_len );
    free( data );
    return ret;
}
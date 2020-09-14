#include <memory>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <string>
#include <iostream>

class SharedMemoryDetacher
{
public:
    void operator()(int *p)
    {
        std::cout << "unlink /tmp1234" << std::endl;
        if (shm_unlink("/tmp1234") != 0)
        {
            std::cerr << "OOPS: shm_unlink() failed" << std::endl;
        }
    }
};

#include <ctype.h> 
#include <errno.h> 
#include <iostream> 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

void CreateFifo(const char FIFO_PATH[])
{
    if( mkfifo(FIFO_PATH, 0666) < 0 )
    {
        std::cerr << "CreateFifo() failed...\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "CreateFifo() succeeded...\n";
}

void Read(const char FIFO_PATH[], char buffer_read[], const int &SIZE, int &fd)
{
    memset(buffer_read, 0, SIZE);

    if( read(fd, buffer_read, SIZE) < 0 )
    {
        std::cerr << "Read() failed...\n";
        close(fd);
        unlink(FIFO_PATH);
        exit(EXIT_FAILURE);        
    }

    std::cout << "Read() succeeded...\n";
    std::cout << "Read content -> " << buffer_read << std::endl;
}

void Write(const char FIFO_PATH[], char buffer_wip[], char buffer_write[], const int &SIZE, int &fd)
{
    memset(buffer_write, 0, SIZE);

    int length = strlen(buffer_wip);

    for(int i = 0; i < length; i++)
    {
        buffer_write[i] = toupper(buffer_wip[i]);
    }

    if( write( fd, buffer_write, length ) < 0 )
    {
        std::cerr << "Write() failed...\n";
        close(fd);
        unlink(FIFO_PATH);
        exit(EXIT_FAILURE);           
    }

    std::cout << "Write() succeeds...\n";
    std::cout << "Write content -> " << buffer_write << std::endl;
}

int main(int argv, char *argc[])
{
    int fd;
    const int SIZE = 30;
    char buffer_read[SIZE];
    char buffer_write[SIZE];

    // 1. set fifo path
    const char FIFO_PATH[] = "/tmp/FifoExample5";

    // 2. create a named FIFO
    CreateFifo(FIFO_PATH);

    // 3. open pipe for r+w
    fd = open(FIFO_PATH, O_RDWR);

    // 4. read from fifo B
    Read(FIFO_PATH, buffer_read, SIZE, fd);
        std::cout << "Fifo1: received -> " << buffer_read << std::endl;

    // 5. process the message and send it back
    // Write(FIFO_PATH, buffer_read, buffer_write, SIZE, fd);

    close(fd);
    unlink(FIFO_PATH);
    return EXIT_SUCCESS;
}
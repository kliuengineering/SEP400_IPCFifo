#include <ctype.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <iostream> 
#include <stdio.h> 
#include <string.h> 
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
}

void Write( const char FIFO_PATH[], char buffer_write[], const int &SIZE, int &fd )
{
    memset(buffer_write, 0, SIZE);
    sprintf(buffer_write, "this is just a simple message.");

    int length = strlen(buffer_write) + 1;
    
    // write stuff
    if( write(fd, buffer_write, length) < 0 )
    {
        std::cerr << "Write() failed...\n";
        close(fd);
        unlink(FIFO_PATH);
        exit(EXIT_FAILURE);
    }
}

void Read( const char FIFO_PATH[], char buffer_read[], const int &SIZE, int &fd )
{
    memset(buffer_read, 0, SIZE);

    if( read(fd, buffer_read, SIZE) < 0 )
    {
        std::cerr << "Read() failed...\n";
        close(fd);
        unlink(FIFO_PATH);
        exit(EXIT_FAILURE);        
    }

    std::cout << "Read content -> " << buffer_read << std::endl;
}

int main(int argc, char *argv[])
{
    // 1. set fifo path
    const char FIFO_PATH[] = "/tmp/FifoExample5";

    int fd;
    const int SIZE = 30;
    char buffer_write[SIZE];
    char buffer_read[SIZE];

    // 2. create a fifo
    // CreateFifo(FIFO_PATH);

    // 3. open fifo file
    fd = open(FIFO_PATH, O_RDWR);

    // 4. write
    Write(FIFO_PATH, buffer_write, SIZE, fd);

    // 5. read
    // Read(FIFO_PATH, buffer_read, SIZE, fd);


    close(fd);
    unlink(FIFO_PATH);
    return EXIT_SUCCESS;    
}
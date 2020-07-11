#include "bloomfilter.h"

#include <fstream>
#include <string>

#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void handle_error(const char *msg)
{
    perror(msg);
    exit(255);
}

static uintmax_t stdread(const std::string fname)
{
    std::string temp;
    std::ifstream input;
    uintmax_t lines = 0;

    input.open(fname.c_str());
    if (input.is_open())
    {
        input >> temp;

        while (input)
        {
            ++lines;
            input >> temp;
        }
        input.close(); 
    }
    else {
        handle_error("open");
    }

    return lines;
}

static uintmax_t wc(char const *fname)
{
    static const auto BUFFER_SIZE = 16 * 1024;
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    char buf[BUFFER_SIZE + 1];
    uintmax_t lines = 0;

    while (size_t bytes_read = read(fd, buf, BUFFER_SIZE))
    {
        if (bytes_read == (size_t)-1)
            handle_error("read failed");
        if (!bytes_read)
            break;

        for (char *p = buf; (p = (char *)memchr(p, '\n', (buf + bytes_read) - p)); ++p)
        {
            ++lines;
        }
    }

    return lines;
}

int main()
{
    //printf("Lines: %lu\n", wc("src/5million.csv"));
    printf("Lines: %lu\n", stdread("src/5million.csv"));
    return 0;
}
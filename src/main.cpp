#include <iostream>
#include <vector>
#include "process.hpp"

int main(int argc, char *argv[])
{
    Process proc;

    if (argc != 2) {
        std::printf("Error: One input is required, exiting\n");
        return -1;
    }

    if (!proc.initialize(argv[1])) {
        return -1;
    }

    proc.do_processing();

    return 0;
}
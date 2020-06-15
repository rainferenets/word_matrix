#include <iostream>
#include <vector>
#include "process_rec.hpp"

int main(int argc, char *argv[])
{
    ProcessRec proc_rec;

    std::vector<std::string> word_ok; 
    std::vector<std::string> word_nok;

    if (argc != 2) {
        std::printf("Error: One input is required, exiting\n");
        return -1;
    }

    if (!proc_rec.get_input_data(argv[1], word_ok, word_nok)) {
        return -1;
    }

    proc_rec.do_processing(word_ok, word_nok);

    return 0;
}
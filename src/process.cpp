#include "process.hpp"

Process::Process() 
{
    hor_line = std::string (matrix_size, '=');
}

Process::~Process() 
{
    if (input_file.is_open()) {
        input_file.close();
    }
}


void Process::prepare_word(const size_t count, const std::string &line, std::vector<std::string> &word_ok, std::vector<std::string> &word_nok)
{
    if (line.length() == 0) {
        std::printf("Info: skipping an empty line (%ld)\n", count);
    }
    else if ((line.length() > 0) && (line.length() <= matrix_size)) {
        word_ok.emplace_back(line);
    }
    else if (line.length() > matrix_size) {
        word_nok.emplace_back(line);
    }
}


bool Process::get_input_data(const std::string &input_file_name, std::vector<std::string> &word_ok, std::vector<std::string> &word_nok)
{
    std::string line;
    size_t count = 0;

    word_ok.clear();
    word_ok.reserve(max_nr_of_words);
    word_nok.clear();
    word_nok.reserve(max_nr_of_words);

    std::printf("Input file name: '%s'\n", input_file_name.c_str());

    input_file.open(input_file_name);
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            prepare_word(count, line, word_ok, word_nok);
            count++;

            if (count == max_nr_of_words) {
                std::printf("Info: reached to the max allowed number of lines (%ld), skipping the rest\n", count);
                return true;
            }
        }
    }
    else {
        std::printf("Error: failed to open input file '%s', exiting\n", input_file_name.c_str());
        return false;
    }

    return true;
}


void Process::fill_word_matrix_plus(std::vector<std::string> &matrix)
{
    for (size_t i = 0; i < matrix.size(); i++) {
        const size_t diff = matrix_size - matrix[i].length();

        if (diff > 0) {
            for (size_t j = 0; j < diff; j++) {
                matrix[i].push_back('+');
            }
        }
    }
}


void Process::print_words(std::vector<std::string> const &words)
{
    std::printf("%s\n", hor_line.c_str());
    for (size_t i = 0; i < words.size(); i++) {
        std::printf("%s\n", words[i].c_str());
    }
    std::printf("%s\n", hor_line.c_str());
}


void Process::print_words(std::vector<std::string> const &words, std::vector<size_t> const &idx)
{
    std::printf("%s\n", hor_line.c_str());
    for (size_t i = 0; i < idx.size(); i++) {
        std::printf("%s\n", words[idx[i]].c_str());
    }
    std::printf("%s\n", hor_line.c_str());
}


void Process::print_output_matrix(std::vector<std::string> &matrix)
{
    std::printf("%s\n", hor_line.c_str());
    for (size_t i = 0; i < matrix.size(); i++) {
        std::printf("%s\n", matrix[i].c_str());
    }
    std::printf("%s\n", hor_line.c_str());
}
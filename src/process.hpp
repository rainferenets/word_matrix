#pragma once

#include "definitions.hpp"
#include <vector>
#include <string>
#include <fstream>

class Process {
private:
    std::ifstream input_file;
    std::string hor_line;

    void prepare_word(size_t count, const std::string &line, std::vector<std::string> &word_ok, std::vector<std::string> &word_nok);

protected:
    void fill_word_matrix_plus(std::vector<std::string> &matrix);
    void print_words(std::vector<std::string> const &words);
    void print_words(std::vector<std::string> const &words, std::vector<size_t> const &idx);
    void print_output_matrix(std::vector<std::string> &matrix);

public:
    bool get_input_data(const std::string &input_file_name, std::vector<std::string> &word_ok, std::vector<std::string> &word_nok);

    Process();
    ~Process();
};
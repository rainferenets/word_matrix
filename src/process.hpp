#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <algorithm>

class Process {
public:
    Process();
    ~Process();

    bool initialize(const std::string &input_file_name);
    void do_processing();

private:
    static constexpr size_t max_word_length = 10;

    std::ifstream input_file;
    std::vector<std::string> word_ok;
    std::vector<std::string> word_nok;
    std::vector<size_t> word_length;
    std::vector<std::string> word_matrix;

    size_t matrix_row_count = 0;
    bool matrix_filled = false;

    bool is_input_size_zero();
    void remove_used_words();
    bool test_single_word(size_t len);
    bool test_double_word(size_t len);
    bool test_triple_word(size_t len);
    bool test_quadruple_word(size_t len);
    bool test_quintuple_word(size_t len);
    bool test_all_words(size_t len);
    bool are_all_words_length_one();
    void add_length_one_words();
    void fill_word_matrix();
    void fill_word_matrix_plus();

    void print_input_words(std::vector<std::string> const &words);
    void print_input_file_content();
    void print_output_matrix();
};

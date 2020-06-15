#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "process.hpp"

class ProcessRec : public Process {
public:
    ProcessRec();

    void do_processing(std::vector<std::string> const &word_ok, std::vector<std::string> const &word_nok);

private:
    size_t nr_of_words;

    std::vector<size_t> word_length;
    std::vector<size_t> word_length_sort;
    std::vector<size_t> idx_sort;
    std::vector<std::string> word_matrix;
    std::vector<std::vector<size_t> > sum_idx;

    size_t matrix_row_count = 0;
    bool matrix_filled = false;

    void sort_word_lengths();
    void clear_word_matrix();
    void fill_word_matrix(std::vector<std::string> const &word);
    void remove_used_words();

    void get_sum(std::vector<size_t> const &num, size_t sum, std::vector<std::vector<size_t> > &comb);
    void get_sum_rec(std::vector<size_t> const &num, std::vector<size_t> const &num_idx, size_t sum, 
        std::vector<size_t> num_part, std::vector<size_t> num_part_idx, std::vector<std::vector<size_t> > &comb);
    bool is_word_unique(std::vector<size_t> curr, std::vector<std::vector<size_t> > &prev);
};

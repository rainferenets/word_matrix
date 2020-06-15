#include "process_rec.hpp"

ProcessRec::ProcessRec() 
{
    word_matrix.resize(matrix_size);
    sum_idx.reserve(max_nr_of_words);
}


void ProcessRec::do_processing(std::vector<std::string> const &word_ok, std::vector<std::string> const &word_nok)
{
    nr_of_words = word_ok.size();

    word_length.reserve(nr_of_words);
    word_length.clear();
    idx_sort.reserve(nr_of_words);
    idx_sort.clear();

    std::printf("\nAccepted length words (<=%ld), used as input:\n", matrix_size);
    print_words(word_ok);

    if (word_nok.size() > 0) {
        std::printf("\nToo long words (>%ld), skipped from input:\n", matrix_size);
        print_words(word_nok);
    }

    for (size_t i = 0; i < nr_of_words; i++) {
        word_length.push_back(word_ok[i].size());
        idx_sort.push_back(i);
    }

    clear_word_matrix();
    sort_word_lengths();
    fill_word_matrix(word_ok);
    fill_word_matrix_plus(word_matrix);

    std::printf("\nOutput matrix (%ldx%ld):\n", matrix_size, matrix_size);
    print_output_matrix(word_matrix);

    if (idx_sort.size() > 0) {
        std::printf("\nRemaining accepted words that did not fit into the matrix:\n");
        print_words(word_ok, idx_sort);
    }
}


void ProcessRec::sort_word_lengths()
{
    word_length_sort.reserve(nr_of_words);
    word_length_sort.clear();

    std::stable_sort(idx_sort.begin(), idx_sort.end(), [&](size_t i1, size_t i2) {return word_length[i1] > word_length[i2];});

    for (size_t i = 0; i < nr_of_words; i++) {
        word_length_sort.push_back(word_length[idx_sort[i]]);
    }
}


void ProcessRec::clear_word_matrix()
{
    for (size_t i = 0; i < word_matrix.size(); i++) {
        word_matrix[i].clear();
    }
}


void ProcessRec::remove_used_words()
{
    idx_sort.erase(std::remove_if(idx_sort.begin(), idx_sort.end(), [&](size_t x){return x == max_nr_of_words;}), idx_sort.end());
    word_length_sort.erase(std::remove_if(word_length_sort.begin(), word_length_sort.end(), [&](size_t x){return x == max_nr_of_words;}), word_length_sort.end());
}


void ProcessRec::fill_word_matrix(std::vector<std::string> const &word)
{
    // Loop over all possible word lengths from 'max_word_length' -> 1
    for (size_t i = matrix_size; i != 0; i--) {
        get_sum(word_length_sort, i, sum_idx);

        for (size_t j = 0; j < sum_idx.size(); j++) {
            std::string line = "";
            for (size_t k = 0; k < sum_idx[j].size(); k++) {
                line += word[idx_sort[sum_idx[j][k]]];

                idx_sort[sum_idx[j][k]] = max_nr_of_words;
                word_length_sort[sum_idx[j][k]] = max_nr_of_words;
            }

            word_matrix[matrix_size-1-matrix_row_count] = line;
            matrix_row_count++;

            if (matrix_row_count == matrix_size) {
                remove_used_words();
                return;
            }
        }

        remove_used_words();

        if (word_length_sort.size() == 0) {
            return;
        }
    }
}


bool ProcessRec::is_word_unique(std::vector<size_t> curr, std::vector<std::vector<size_t> > &prev)
{
    for (size_t i = 0; i < prev.size(); i++) {
        for (size_t j = 0; j < prev[i].size(); j++) {
            for (size_t k = 0; k < curr.size(); k++) {
                if (prev[i][j] == curr[k]) {
                    return false;
                }
            }
        }
    }
    return true;
}


void ProcessRec::get_sum_rec(std::vector<size_t> const &num, std::vector<size_t> const &num_idx, size_t sum, 
    std::vector<size_t> num_part, std::vector<size_t> num_part_idx, std::vector<std::vector<size_t> > &comb)
{
    size_t s = std::accumulate(num_part.begin(), num_part.end(), 0);

    if (s == sum) {
        if (is_word_unique(num_part_idx, comb)) { // use only unique combinations, no repetitions are allowed
            comb.push_back(num_part_idx);
        }
    }

    if (s >= sum) {
        return;
    }

    for (size_t i = 0; i < num.size(); i++) {
        std::vector<size_t> num_rem = std::vector<size_t>(num.begin()+i+1, num.end());
        std::vector<size_t> num_part_rec(num_part.size()+1);
        std::copy(num_part.begin(), num_part.end(), num_part_rec.begin());
        num_part_rec.back() = num[i];

        std::vector<size_t> num_idx_rem = std::vector<size_t>(num_idx.begin()+i+1, num_idx.end());
        std::vector<size_t> num_part_idx_rec(num_part_idx.size()+1);
        std::copy(num_part_idx.begin(), num_part_idx.end(), num_part_idx_rec.begin());
        num_part_idx_rec.back() = num_idx[i];

        get_sum_rec(num_rem, num_idx_rem, sum, num_part_rec, num_part_idx_rec, comb);
    }
}


void ProcessRec::get_sum(std::vector<size_t> const &num, size_t sum, std::vector<std::vector<size_t> > &comb)
{
    std::vector<size_t> word_idx(num.size());
    std::iota(word_idx.begin(), word_idx.end(), 0);
    comb.clear();

    get_sum_rec(num, word_idx, sum, {}, {}, comb);
}
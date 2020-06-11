#include "process.hpp"

Process::Process() {}

Process::~Process() {input_file.close();}

// Initialization for the word processing
bool Process::initialize(const std::string &input_file_name)
{
    std::string line;
    size_t count = 0;

    std::printf("Input file name: '%s'\n", input_file_name.c_str());

    input_file.open(input_file_name);
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.length() == 0) {
                std::printf("Info: skipping an empty line (%ld)\n", count);
            }
            else if ((line.length() > 0) && (line.length() <= max_word_length)) {
                word_ok.emplace_back(line);
            }
            else if (line.length() > max_word_length) {
                word_nok.emplace_back(line);
            }

            count++;
        }
        
    }
    else {
        std::printf("Error: failed to open input file '%s', exiting\n", input_file_name.c_str());
        return false;
    }

    word_matrix.resize(max_word_length);

    return true;
}


// High level method for word processing
void Process::do_processing()
{
    print_input_file_content();
    fill_word_matrix();
    print_output_matrix();

    if (word_ok.size() > 0) {
        std::printf("\nRemaining words that did not fit into the matrix:\n");
        print_input_words(word_ok);
    }
}


// Test if the input size is zero or not
bool Process::is_input_size_zero()
{
    if (word_ok.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}


// Remove used words from the data buffers
void Process::remove_used_words()
{
    word_ok.erase(std::remove(word_ok.begin(), word_ok.end(), ""), word_ok.end());
    word_length.erase(std::remove(word_length.begin(), word_length.end(), 0), word_length.end());
}


// Test single words
bool Process::test_single_word(const size_t len)
{
    for (size_t i = 0; i < word_length.size(); i++) {
        word_length[i] = word_ok[i].length();

        if (word_length[i] == len) {
            word_matrix[max_word_length-1-matrix_row_count] = word_ok[i];
            matrix_row_count++;

            word_ok[i] = "";
            word_length[i] = 0;
        }

        if (matrix_row_count == max_word_length - 0) {
            matrix_filled = true;
            return false;
        }
    }

    return true;
}


// Test combinations of 1 words
bool Process::test_double_word(const size_t len)
{
    size_t n1, n2;

    for (size_t i = 0; i < word_ok.size(); i++) {
        n1 = word_ok[i].length();
        for (size_t j = i+1; j < word_ok.size(); j++) {
            n2 = word_ok[j].length();

            if ((n1+n2 == len) && (word_length[i] != 0) && (word_length[j] != 0)) {
                word_matrix[max_word_length-1-matrix_row_count] = word_ok[i] + word_ok[j];
                matrix_row_count++;

                word_ok[i] = "";
                word_length[i] = 0;
                word_ok[j] = "";
                word_length[j] = 0;
            }

            if (matrix_row_count == max_word_length - 0) {
                matrix_filled = true;
                return false;
            }
        }
    }

    return true;
}


// Test combinations of 3 words
bool Process::test_triple_word(const size_t len)
{
    size_t n1, n2, n3;

    for (size_t i = 0; i < word_ok.size(); i++) {
        n1 = word_ok[i].length();
        for (size_t j = i+1; j < word_ok.size(); j++) {
            n2 = word_ok[j].length();
            for (size_t k = j+1; k < word_ok.size(); k++) {
                n3 = word_ok[k].length();

                if ((n1+n2+n3 == len) && (word_length[i] != 0) && (word_length[j] != 0) && (word_length[k] != 0)) {
                    word_matrix[max_word_length-1-matrix_row_count] = word_ok[i] + word_ok[j] + word_ok[k];
                    matrix_row_count++;

                    word_ok[i] = "";
                    word_length[i] = 0;
                    word_ok[j] = "";
                    word_length[j] = 0;
                    word_ok[k] = "";
                    word_length[k] = 0;
                }

                if (matrix_row_count == max_word_length - 0) {
                    matrix_filled = true;
                    return false;
                }
            }
        }
    }

    return true;
}


// Test combinations of 1 words
bool Process::test_quadruple_word(const size_t len)
{
    size_t n1, n2, n3, n4;

    for (size_t i = 0; i < word_ok.size(); i++) {
        n1 = word_ok[i].length();
        for (size_t j = i+1; j < word_ok.size(); j++) {
            n2 = word_ok[j].length();
            for (size_t k = j+1; k < word_ok.size(); k++) {
                n3 = word_ok[k].length();
                for (size_t q = k+1; q < word_ok.size(); q++) {
                    n4 = word_ok[q].length();

                    if ((n1+n2+n3+n4 == len) && (word_length[i] != 0) && (word_length[j] != 0) && (word_length[k] != 0) && (word_length[q] != 0)) {
                        word_matrix[max_word_length-1-matrix_row_count] = word_ok[i] + word_ok[j] + word_ok[k] + word_ok[q];
                        matrix_row_count++;

                        word_ok[i] = "";
                        word_length[i] = 0;
                        word_ok[j] = "";
                        word_length[j] = 0;
                        word_ok[k] = "";
                        word_length[k] = 0;
                        word_ok[q] = "";
                        word_length[q] = 0;
                    }

                    if (matrix_row_count == max_word_length - 0) {
                        matrix_filled = true;
                        return false;
                    }
                }
            }
        }
    }

    return true;
}


// Test combinations of 5 words
bool Process::test_quintuple_word(const size_t len)
{
    size_t n1, n2, n3, n4, n5;

    for (size_t i = 0; i < word_ok.size(); i++) {
        n1 = word_ok[i].length();
        for (size_t j = i+1; j < word_ok.size(); j++) {
            n2 = word_ok[j].length();
            for (size_t k = j+1; k < word_ok.size(); k++) {
                n3 = word_ok[k].length();
                for (size_t q = k+1; q < word_ok.size(); q++) {
                    n4 = word_ok[q].length();
                    for (size_t p = q+1; p < word_ok.size(); p++) {
                        n5 = word_ok[p].length();

                        if ((n1+n2+n3+n4+n5 == len) && (word_length[i] != 0) && (word_length[j] != 0) && (word_length[k] != 0) && (word_length[q] != 0) && (word_length[p] != 0)) {
                            word_matrix[max_word_length-1-matrix_row_count] = word_ok[i] + word_ok[j] + word_ok[k] + word_ok[q] + word_ok[p];
                            matrix_row_count++;

                            word_ok[i] = "";
                            word_length[i] = 0;
                            word_ok[j] = "";
                            word_length[j] = 0;
                            word_ok[k] = "";
                            word_length[k] = 0;
                            word_ok[q] = "";
                            word_length[q] = 0;
                            word_ok[p] = "";
                            word_length[p] = 0;
                        }

                        if (matrix_row_count == max_word_length - 0) {
                            matrix_filled = true;
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}


// Test different word combinations
bool Process::test_all_words(size_t len)
{
    for (size_t i = 1; i <= 5; i++) {
        if (is_input_size_zero()) {
            return false;
        }

        if (are_all_words_length_one()) {
            add_length_one_words();
            return false;
        }

        switch (i) {
        case 1:
            test_single_word(len);
            break;

        case 2:
            test_double_word(len);
            break;

        case 3:
            test_triple_word(len);
            break;

        case 4:
            test_quadruple_word(len);
            break;

        case 5:
            test_quintuple_word(len);
            break;
        }

        remove_used_words();

        if (matrix_filled) {
            return false;
        }
    }

    return true;
}


// Check if all words in vector have length 1
bool Process::are_all_words_length_one()
{
    if (std::all_of(word_length.begin(), word_length.end(), [](int i){return i==1;})) {
        return true;
    }
    else {
        return false;
    }
}


// Add length 1 words to the end of rows where possible
void Process::add_length_one_words()
{
    for (size_t i = max_word_length; i >= 1; i--) {
        if (word_ok.size() > 0) {
            const size_t diff = max_word_length - word_matrix[i-1].length();

            for (size_t j = 0; j < diff; j++) {
                word_matrix[i-1].push_back(word_ok.back()[0]);
                word_ok.pop_back();

                if (word_ok.size() == 0) {
                    break;
                }
            }
        }
    }
}


// Fill output matrix with necessary plus signs
void Process::fill_word_matrix_plus()
{
    for (size_t i = 0; i < word_matrix.size(); i++) {
        const size_t diff = max_word_length - word_matrix[i].length();

        if (diff > 0) {
            for (size_t j = 0; j < diff; j++) {
                word_matrix[i].push_back('+');
            }
        }
    }
}


void Process::fill_word_matrix()
{
    word_length.resize(word_ok.size());

    for (size_t i = max_word_length; i >= 1; i--) {
        if (!test_all_words(i)) break;
    }

    fill_word_matrix_plus();
}


void Process::print_input_words(std::vector<std::string> const &words)
{
    std::printf("==========\n");
    for (size_t i = 0; i < words.size(); i++) {
        std::printf("%s\n", words[i].c_str());
    }
    std::printf("==========\n");
}


void Process::print_input_file_content()
{
    std::printf("\nAccepted length words, used as input:\n");
    print_input_words(word_ok);

    if (word_nok.size() > 0) {
        std::printf("\nToo long words, skipped from input:\n");
        print_input_words(word_nok);
    }
}


void Process::print_output_matrix()
{
    std::printf("\nOutput matrix:\n");
    std::printf("==========\n");
    for (size_t i = 0; i < max_word_length; i++) {
        std::printf("%s\n", word_matrix[i].c_str());
    }
    std::printf("==========\n");
}
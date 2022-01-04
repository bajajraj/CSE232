/**
 * @file code.cpp
 * @author Rajaditya Shrikishan Bajaj
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// This function returns a vector of strings in with each word of the string
// being a unique element in the vector. It helps in working with strings.
std::vector<std::string> ChangeVectorList(const std::string& s) {
    std::stringstream iss(s);
    std::string word;
    std::vector<std::string> new_vector;
    while (iss >> word) {
        new_vector.push_back(word);
    }
    return new_vector;
}

// Returns a True boolean if the two given strings fulfills the criteria of
// merging else returns a Fasle boolean.
bool ConfirmMerge(const std::string& string_1, const std::string& string_2) {
    // this loop is required to deduce the first string into shorter string with 1
    // starting character being removed in each loop.
    for (int j = 0; j < static_cast<int>(string_1.length()); ++j) {
        // this loop is required to deduce the later string into smaller string with
        // 1 character being removed in every loop.
        for (int i = static_cast<int>(string_2.length()); i > 0; --i) {
            if (string_1.substr(j) == string_2.substr(0, i)) {
                return true;
            } else {
                continue;
            }
        }
    }
    return false;
}

// Returns a string that is in the merge form for the first and the second
// string.
std::string ConvertedOutput(const std::string& string_1,
        const std::string& string_2) {
    int same_char_count = 0;
    std::string str_1_rem;
    for (int i = same_char_count; i < static_cast<int>(string_1.size()); ++i) {
        if (string_1[i] == string_2[0]) {
            same_char_count = i;  // this int is equal to the index where the i
            // character of the first string is equal to second
            // string. It helps in finding the index from where
            // merging should start.
            break;
        }
    }
    str_1_rem = string_1.substr(same_char_count);
    int same_char_pos;
    // Check if the string from i index is part of the following string.
    if (string_2.find(str_1_rem) != std::string::npos) {
        same_char_pos = same_char_count;
    } else {  // if not part of the string, then changes the position to starting
        // position.
        same_char_pos = 0;
    }
    std::string merge_str;
    std::string str1 = string_1.substr(same_char_pos);
    int str2_start = static_cast<int>(str1.length());
    merge_str = string_1 + string_2.substr(str2_start);

    return merge_str;
}

// Essential in returning the vector of string into the necessary merged formed
// where merging is needed.
std::vector<std::string> ConvertedVector(std::vector<std::string>& v) {
    std::vector<std::string> new_vector;
    v.push_back("");  // it helps in working with the last string and prevents
    // std::out_of_index error.
    int v_size = static_cast<int>(v.size()) - 1;
    for (int i = 0; i < v_size; ++i) {
        std::string str1 = v[i];
        std::string str2 = v[i + 1];
        if (ConfirmMerge(str1, str2) != 0) {
            std::string k = ConvertedOutput(str1, str2);
            new_vector.push_back(k);
            ++i;
        } else {
            std::string k = str1;
            new_vector.push_back(k);
        }
    }
    return new_vector;
}

// Returns a vector of string after the looping size of input vector time to
// merge more than two words simultaneously.
std::vector<std::string> LoopVector(const std::vector<std::string>& v) {
    std::vector<std::string> looped_vector;
    looped_vector = v;
    // assigns the input vector to new vector to work with loop.
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        looped_vector = ConvertedVector(looped_vector);
    }
    return looped_vector;
}

int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        std::vector<std::string> string_vector = ChangeVectorList(s);
        std::vector<std::string> answer_vector = LoopVector(string_vector);
        for (auto e : answer_vector) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}



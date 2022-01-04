#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "redact.h"

std::string redact_all_chars(const std::string& input_str) {
  // this function replaces every character in the string with "#".
  std::string out_str;
  for (int i = 0; i < static_cast<int>(input_str.size()); ++i) {
    out_str += "#";
  }
  return out_str;
}

std::string redact_alphabet_digits(const std::string& input_str) {
  // this function replaces character from "A-Z", "a-z", and "0-9" with a "#".
  std::string out_str;
  for (int i = 0; i < static_cast<int>(input_str.size()); ++i) {
    if ((input_str[i] > 47) && (input_str[i] < 58)) {
      out_str += "#";
    } else if ((input_str[i] > 96) && (input_str[i] < 123)) {
      out_str += "#";
    } else if ((input_str[i] > 64) && (input_str[i] < 91)) {
      out_str += "#";
    } else {
      out_str += input_str[i];
    }
  }
  return out_str;
}

std::vector<std::string> replace_hash(const std::vector<std::string>& in_vec) {
  // this function makes a new string equal consisting of "#" of equal size of
  // the input string.
  std::vector<std::string> replaced_vec;
  for (int i = 0; i < static_cast<int>(in_vec.size()); ++i) {
    std::string word = in_vec[i];
    std::string replaced_word;
    for (int j = 0; j < static_cast<int>(word.size()); ++j) {
      replaced_word += "#";
    }
    replaced_vec.push_back(replaced_word);
  }
  return replaced_vec;
}

std::string redact_words(const std::string& input_str,
                         const std::vector<std::string>& inp_vec) {
  // this function change the required word given in the vector with "#".
  std::string out_str;
  std::string copy_str = input_str;
  std::vector<std::string> replace_vec = replace_hash(inp_vec);
  // this vector contains "#" of strings for each vector of string.
  for (int i = 0; i < static_cast<int>(inp_vec.size()); ++i) {
    std::string find_word = inp_vec[i];
    // this was given in
    // this.pointer.com/find-and-replace-all-occurences-of-a-sub-string-in-c.
    size_t pos = copy_str.find(find_word);  // find the given word.
    while (pos != std::string::npos) {
      copy_str.replace(pos, find_word.size(),
                        replace_vec[i]);  // replace the given word.
      pos = copy_str.find(find_word, pos + find_word.size());
    }
  }
  return copy_str;
}

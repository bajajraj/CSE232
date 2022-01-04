#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

#include "self_destructing.h"
#include "redact.h"

SelfDestructingMessage::SelfDestructingMessage() {
  // assigning default values to the parameters.
  messages = {};
  number_of_allowed_views = 0;
  timed_view = {};
}

SelfDestructingMessage::SelfDestructingMessage(
    std::vector<std::string> in_message, long view_allowed) {
  // assigning the input value to the parameters.
  messages = in_message;
  number_of_allowed_views = view_allowed;
  std::vector<long> timed_view_copy(
      static_cast<int>(in_message.size()),
      view_allowed);  // https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/
  // we will need to make a new vector using number_of_allowed_views.
  timed_view = timed_view_copy;
}

int SelfDestructingMessage::size() {
  // this function returns the size of the messages vector, i.e., the number of
  // messages it has.
  int messages_size = static_cast<int>(messages.size());
  return messages_size;
}

std::vector<std::string> SelfDestructingMessage::get_redacted() {
  // this function redacts all the string inside the messages vector and outputs
  // a new vector containing strings in redacted from.
  std::vector<std::string> get_redacted_vec;
  for (int i = 0; i < static_cast<int>(messages.size()); ++i) {
    std::string str = redact_alphabet_digits(messages[i]);
    get_redacted_vec.push_back(str);
  }
  return get_redacted_vec;
}

long SelfDestructingMessage::number_of_views_remaining(int index) {
  // this function gives the number of views remaining for a given string.
  long long_index = static_cast<long>(index);
  long views_remaining = timed_view[long_index];
  return views_remaining;
}

std::string const& SelfDestructingMessage::operator[](size_t index) {
  // this function gives the actual message and follows the given rule while
  // showing the accessing the message.
  if ((index < 0) || (index >= messages.size())) {  // if index is not proper
    throw std::out_of_range("Invalid Index");
  } else if (timed_view[index] != 0) {  // if view remained is not equal to 0.
    long num_view = timed_view[index];
    long view_remain = num_view - 1;  // subtracting 1 from the given views.
    timed_view.at(index) = view_remain;
    return messages[index];
  } else {  // if no views remain.
    throw std::invalid_argument("No views remained.");
  }
}

std::ostream& operator<<(std::ostream& out, const SelfDestructingMessage& sdm) {
  // this function returns the messages in ostream form where they are in
  // redacted form.
  // std::vector<std::string> redact_vector = sdm.get_redacted();
  for (int i = 0; i < static_cast<int>(sdm.messages.size()); ++i) {
    out << "0" << sdm.timed_view[i] << ": "
        << redact_alphabet_digits(sdm.messages[i]) << std::endl;
  }
  return out;
}

SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage& sdm) {
  // this function copies the SelfDestructingMessage function with zero out all
  // the timed_view vector of the original class.
  messages = sdm.messages;
  number_of_allowed_views = sdm.number_of_allowed_views;
  timed_view = sdm.timed_view;
  // this step helps in zero out the original class.
  std::vector<long> timed_view_copy(static_cast<int>(sdm.messages.size()), 0);
  sdm.timed_view = timed_view_copy;
}

SelfDestructingMessage& SelfDestructingMessage::operator=(
    SelfDestructingMessage& sdm) {
  // this function copies and transfer all the views remaining to the copy, and
  // zero out the original.
  messages = sdm.messages;
  number_of_allowed_views = sdm.number_of_allowed_views;
  timed_view = sdm.timed_view;
  // this step helps in zero out the original class.
  std::vector<long> timed_view_copy(static_cast<int>(sdm.messages.size()), 0);
  sdm.timed_view = timed_view_copy;
  return *this;
}

void operator>>(std::istream& in, SelfDestructingMessage& sdm) {
  // this function extracts a line from the istream and append it to the message
  // list.
  std::string s;
  std::getline(in, s);  // took help from a TA in the help room.
  sdm.messages.push_back(s);
  long num_view = sdm.number_of_allowed_views;
  sdm.timed_view.push_back(num_view);
}

void SelfDestructingMessage::add_array_of_lines(std::string* ary1, long size) {
  // this function takes an array of strings and push_back the string in
  // messages vector and number_of_allowed_views in timed_view vector.
  for (long i = 0; i < size; i++) {
    messages.push_back(ary1[i]);
    timed_view.push_back(number_of_allowed_views);
  }
}

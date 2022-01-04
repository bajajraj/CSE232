#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include <string>
#include <vector>
#include <ios>

class SelfDestructingMessage {
 private:
  // parameters :
  std::vector<std::string> messages;
  long number_of_allowed_views;
  std::vector<long> timed_view;  // timed_view helps in storing the number of
                                 // times a message has been seen. It is a data
                                 // structure which will be easiest to work with
                                 // as we can use also maps, but working with
                                 // maps is harder than working with vectors.

 public:
  // constructors :
  SelfDestructingMessage();
  SelfDestructingMessage(std::vector<std::string>, long);

  // member functions :
  int size();
  std::vector<std::string> get_redacted();
  long number_of_views_remaining(int);

  // Copy constructor :
  SelfDestructingMessage(SelfDestructingMessage &);

  // member overloaded operaters :
  std::string const &operator[](size_t);
  // help taken from
  // https://www.tutorialspoint.com/cplusplus/subscripting_operator_overloading.htm
  // to work with [] operator.

  // Assign constructor :
  SelfDestructingMessage &operator=(SelfDestructingMessage &);

  // functions overloaded operaters :
  friend std::ostream &operator<<(std::ostream &,
                                  const SelfDestructingMessage &);
  friend void operator>>(std::istream &, SelfDestructingMessage &);

  void add_array_of_lines(std::string *, long);
};

#endif

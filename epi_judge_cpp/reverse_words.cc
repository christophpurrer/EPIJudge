#include <string>
#include <sstream>
#include <iostream>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"

using std::string;

void ReverseWords(string *s) {
    std::reverse(s->begin(), s->end());
    int32_t start = 0, end = s->size();
    while ((end = s->find(" ", start)) != string::npos) {
        // Reverse each word
        std::reverse(s->begin() + start, s->begin() + end);
        start = end + 1;
    }
    // Reverse last word
    std::reverse(s->begin() + start, s->end());
}

string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}

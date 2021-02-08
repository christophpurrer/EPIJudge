#include <string>
#include <sstream>

#include "test_framework/generic_test.h"

using std::string;

int Evaluate(const string &expression) {
    std::stringstream stream(expression);
    std::string segment;
    std::stack<int> stack;
    while (std::getline(stream, segment, ',')) {
        // Handle operands
        if (segment.length() == 1 && !isnumber(segment[0])) {
            auto b = stack.top();
            stack.pop();
            auto a = stack.top();
            stack.pop();
            switch (segment[0]) {
                case '+':
                    stack.emplace(a + b);
                    break;
                case '-':
                    stack.emplace(a - b);
                    break;
                case '*':
                    stack.emplace(a * b);
                    break;
                case '/':
                    stack.emplace(a / b);
                    break;
            }
            // Add digit
        } else {
            stack.emplace(std::stoi(segment));
        }
    }
    return stack.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}

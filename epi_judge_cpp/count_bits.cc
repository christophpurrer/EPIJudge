#include "test_framework/generic_test.h"

short CountBits(unsigned int x) {
  short num_bits = 0;
  auto a = 1|2;
  auto b = 6&4;
  auto c = 8>>1;
  auto d = 1<<10;
  auto e = ~0;
  int32_t xx = 14;
  auto f = xx - '0';
  while (x) {
      num_bits += x & 1;
      x >>= 1;
  }
  return num_bits;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                         DefaultComparator{}, param_names);
}

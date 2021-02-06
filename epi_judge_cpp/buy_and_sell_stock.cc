#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

double BuyAndSellStockOnce(const vector<double> &prices) {
    double minSoFar = prices[0];
    double profit = 0.0;
    for (auto price: prices) {
        minSoFar = std::min(minSoFar, price);
        profit = std::max(profit, price - minSoFar);
    }
    return profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}

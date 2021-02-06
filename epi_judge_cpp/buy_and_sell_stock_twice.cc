#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

double BuyAndSellStockTwice(const vector<double> &prices) {
    double max_total_profit = 0;
    vector<double> first_buy_sell_profits(prices.size(), 0);
    double min_price_so_far = std::numeric_limits<double>::max();

    // forward phase
    for (int i = 0; i < prices.size(); i++) {
        min_price_so_far = std::min(min_price_so_far, prices[i]);
        max_total_profit = std::max(max_total_profit, prices[i] - min_price_so_far);
        first_buy_sell_profits[i] = max_total_profit;
    }
    // backward phase
    double max_price_so_far = std::numeric_limits<double>::min();
    for (int i = prices.size() - 1; i > 0; i--) {
        max_price_so_far = std::max(max_price_so_far, prices[i]);
        max_total_profit = std::max(max_total_profit, max_price_so_far - prices[i] + first_buy_sell_profits[i - 1]);
    }

    return max_total_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}

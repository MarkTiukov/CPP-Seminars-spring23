#include <iostream>
#include <vector>

/// You are given an array prices where prices[i]
/// is the price of a given stock on the ith day.
///
/// You want to maximize your profit by choosing
/// a single day to buy one stock and choosing a
/// different day in the future to sell that stock.
///
/// Return the maximum profit you can achieve from this transaction.
/// If you cannot achieve any profit, return 0

size_t MaxProfit(std::vector<size_t>& prices) {
  size_t minPrice = SIZE_MAX;
  size_t maxProfit = 0;
  for (auto price_iter = prices.begin(); price_iter < prices.end(); price_iter++) {
    size_t current_price = *price_iter;
    if (current_price < minPrice) {
      minPrice = current_price;
    } else if (current_price - minPrice > maxProfit) {
      maxProfit = current_price - minPrice;
    }
  }
  return maxProfit;
}

int main() {
  std::vector<size_t> prices{7,1,5,3,6,4}; // -> 5
//  std::vector<size_t> prices{7,6,4,3,1}; // -> 0

  std::cout << MaxProfit(prices) << std::endl;
}
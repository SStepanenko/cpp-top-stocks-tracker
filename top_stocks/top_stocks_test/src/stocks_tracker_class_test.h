////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stocks_tracker_class_test.h
/// @brief Test of Stocks_tracker class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STOCKS_TRACKER_CLASS_TEST_H
#define STOCKS_TRACKER_CLASS_TEST_H

#include "gtest/gtest.h"

class StocksTrackerClassTest : public ::testing::Test
{
public:

  static bool check_stocks_for_price_change_ascending_sort(const std::vector<std::shared_ptr<Stock_info>>& stocks);

  static bool check_stocks_for_price_change_descending_sort(const std::vector<std::shared_ptr<Stock_info>>& stocks);

  static bool compare_stocks_contents(const std::vector<std::shared_ptr<Stock_info>>& stocks_vector1,
    const std::vector<std::shared_ptr<Stock_info>>& stocks_vector2);

  static void verify_gainers(const std::vector<std::shared_ptr<Stock_info>>& gainers_expected,
    const std::vector<std::shared_ptr<Stock_info>>& gainers_actual);

  static void verify_losers(const std::vector<std::shared_ptr<Stock_info>>& losers_expected,
    const std::vector<std::shared_ptr<Stock_info>>& losers_actual);

private:

}; // class StocksTrackerClassTest

#endif // STOCKS_TRACKER_CLASS_TEST_H

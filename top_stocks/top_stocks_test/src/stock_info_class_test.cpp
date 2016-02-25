////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stock_info_class_test.cpp
/// @brief Test of Stock_info class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "stock_info_class_test.h"

void StockInfoClassTest::verify_stock_info(int32_t stock_id, double first_price, double last_price, double new_price)
{
  Stock_info stock_info(stock_id, first_price, last_price);

  EXPECT_EQ(stock_id, stock_info.get_id());
  EXPECT_DOUBLE_EQ(first_price, stock_info.get_first_price());
  EXPECT_DOUBLE_EQ(last_price, stock_info.get_last_price());

  double price_change_expected = 0.0;

  price_change_expected = _calculate_price_change_percent(first_price, last_price);

  EXPECT_DOUBLE_EQ(price_change_expected, stock_info.get_price_change_percent());

  stock_info.update_price(new_price);

  price_change_expected = _calculate_price_change_percent(first_price, new_price);

  EXPECT_DOUBLE_EQ(price_change_expected, stock_info.get_price_change_percent());
}

double StockInfoClassTest::_calculate_price_change_percent(double first_price, double last_price)
{
  assert(first_price > 0.0);
  assert(last_price > 0.0);

  double result = ((last_price - first_price) / first_price) * 100.0;

  return result;
}

TEST(StockInfoClassTest, VerifyStockInfo)
{
  StockInfoClassTest::verify_stock_info(0, 123.4, 145.6, 235.7);

  StockInfoClassTest::verify_stock_info(9999, 234.67, 234.67, 123.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stock_info_class_test.h
/// @brief Test of Stock_info class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STOCK_INFO_CLASS_TEST_H
#define STOCK_INFO_CLASS_TEST_H

#include "gtest/gtest.h"

class StockInfoClassTest : public ::testing::Test 
{
public:  

  static void verify_stock_info(int32_t stock_id, double first_price, double last_price, double new_price);

private:

  static double _calculate_price_change_percent(double first_price, double last_price);  

}; // class StockInfoClassTest

#endif // STOCK_INFO_CLASS_TEST_H


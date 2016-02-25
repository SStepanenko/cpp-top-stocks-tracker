////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stocks_info.cpp
/// @brief Implementation of the Stock_info class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Stock_info class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Stock_info::calculate_price_change_percent(double first_price, double last_price)
{
  assert(first_price > 0.0);
  assert(last_price > 0.0);

  double result = ((last_price - first_price) / first_price) * 100.0;

  return result;
}

Stock_info::Stock_info(int32_t stock_id, double first_price, double last_price) :
  m_id(stock_id),
  m_first_price(first_price),
  m_last_price(last_price)
{
  assert(stock_id >= 0);
  assert(first_price > 0.0);
  assert(last_price > 0.0);

  m_price_change_percent = calculate_price_change_percent(first_price, last_price);
}

Stock_info::~Stock_info()
{

}

void Stock_info::update_price(double new_price)
{
  assert(new_price > 0.0);

  m_last_price = new_price;

  m_price_change_percent = calculate_price_change_percent(m_first_price, m_last_price);
}

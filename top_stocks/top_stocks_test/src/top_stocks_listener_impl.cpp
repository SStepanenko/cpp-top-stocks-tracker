////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file top_stocks_listener_impl.cpp
/// @brief Implementation of the Top_stocks_listener_impl class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

using namespace std;

Top_stocks_listener_impl::Top_stocks_listener_impl()
{

}

Top_stocks_listener_impl::~Top_stocks_listener_impl()
{

}

void Top_stocks_listener_impl::on_top_gainers_change(const vector<shared_ptr<Stock_info>>& top_gainers)
{
  m_top_gainers = top_gainers;
}

void Top_stocks_listener_impl::on_top_losers_change(const vector<shared_ptr<Stock_info>>& top_losers)
{
  m_top_losers = top_losers;
}

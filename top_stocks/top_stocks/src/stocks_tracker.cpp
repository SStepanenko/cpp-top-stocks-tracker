////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stocks_tracker.cpp
/// @brief Implementation of the Stocks_tracker class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Stocks_tracker class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int32_t Stocks_tracker::s_max_stocks_count = 10000;

const int32_t Stocks_tracker::s_top_stocks_list_size = 10;

const int32_t Stocks_tracker::s_invalid_index = -1;

Stocks_tracker::Stocks_tracker()
{
  m_top_gainers.reserve(s_top_stocks_list_size); // exception
  m_top_losers.reserve(s_top_stocks_list_size); // exception
}

Stocks_tracker::~Stocks_tracker()
{

}

void Stocks_tracker::on_quote(int32_t stock_id, double new_price)
{
  if (stock_id < 0 || stock_id >= s_max_stocks_count)
  {
    throw invalid_argument("stock_id");
  }

  if (new_price <= 0.0)
  {
    throw invalid_argument("price");
  }

  bool top_gainers_changed = false;
  bool top_losers_changed = false;

  bool is_new_stock = false;

  // Get stock info by ID.
  shared_ptr<Stock_info> stock_info = m_stocks_map[stock_id];

  if (stock_info != nullptr)
  { // Stock info was already got earlier.
    _update_stock_in_sorted_list(stock_info, new_price, top_gainers_changed, top_losers_changed); // exception
  }
  else
  { // Stock with given ID appeared for the first time.   

    stock_info = make_shared<Stock_info>(stock_id, new_price, new_price); // exception

    m_stocks_map[stock_id] = stock_info;

    _insert_new_stock_in_sorted_list(stock_info, top_gainers_changed, top_losers_changed); // exception
  }

  // Notify about top gainers change.
  if (top_gainers_changed)
  {
    _update_top_gainers_and_raise_event();
  }

  // Notify about top losers change.
  if (top_losers_changed)
  {
    _update_top_losers_and_raise_event();
  }
}

void Stocks_tracker::clear()
{
  m_stocks_map.clear();

  m_sorted_stocks.clear();  

  _update_top_gainers_and_raise_event();
  _update_top_losers_and_raise_event();
}

void Stocks_tracker::_update_top_gainers_and_raise_event()
{
  m_top_gainers.clear();

  for (auto iterator = m_sorted_stocks.begin(); iterator != m_sorted_stocks.end(); iterator++)
  {
    const shared_ptr<Stock_info>& stock_info = *iterator;

    if (stock_info->get_price_change_percent() > 0.0 &&
      static_cast<int32_t>(m_top_gainers.size()) < s_top_stocks_list_size)
    {
      m_top_gainers.push_back(stock_info);
    }
    else
    {
      break;
    }
  } // for

  if (m_top_stocks_listener != nullptr)
  {
    m_top_stocks_listener->on_top_gainers_change(m_top_gainers);
  }
}

void Stocks_tracker::_update_top_losers_and_raise_event()
{
  m_top_losers.clear();

  for (auto iterator = m_sorted_stocks.crbegin(); iterator != m_sorted_stocks.crend(); iterator++)
  {
    const shared_ptr<Stock_info>& stock_info = *iterator;

    if (stock_info->get_price_change_percent() < 0.0 &&
      static_cast<int32_t>(m_top_losers.size()) < s_top_stocks_list_size)
    {
      m_top_losers.push_back(stock_info);
    }
    else
    {
      break;
    }
  } // for

  if (m_top_stocks_listener != nullptr)
  {
    m_top_stocks_listener->on_top_losers_change(m_top_losers);
  }
}

int32_t Stocks_tracker::_remove_stock_from_sorted_list(const shared_ptr<Stock_info>& stock_info)
{
  assert(stock_info != nullptr);

  int32_t position = -1;

  for (auto iterator = m_sorted_stocks.begin(); iterator != m_sorted_stocks.end(); iterator++)
  {
    position++;

    if ((*iterator) == stock_info)
    {
      m_sorted_stocks.erase(iterator); // exception          
      break;
    }
  } // for

  return position;
}

void Stocks_tracker::_insert_new_stock_in_sorted_list(const shared_ptr<Stock_info>& stock_info,
  bool& top_gainers_changed, bool& top_losers_changed)
{
  assert(stock_info != nullptr);

  if (m_sorted_stocks.empty())
  { // List of stocks is empty.

    m_sorted_stocks.push_back(stock_info); // exception

    top_gainers_changed = (stock_info->get_price_change_percent() > 0.0);
    top_losers_changed = (stock_info->get_price_change_percent() < 0.0);
  }
  else
  { // Stock is already contained in list.

    int32_t position = -1;

    if (stock_info->get_price_change_percent() <= m_sorted_stocks.back()->get_price_change_percent())
    { // Price change is less than price change of the last element in list (smallest price change).

      // Store position of the added stock.
      position = m_sorted_stocks.size();

      // Add stock to the end of list.
      m_sorted_stocks.push_back(stock_info); // exception
    }
    else
    { // Look for the place to insert new stock.

      for (auto iterator = m_sorted_stocks.begin(); iterator != m_sorted_stocks.end(); iterator++)
      {
        position++;

        if (stock_info->get_price_change_percent() > (*iterator)->get_price_change_percent())
        {
          m_sorted_stocks.insert(iterator, stock_info); // exception          

          break;
        }
      } // for
    }

    assert(position >= 0);

    top_gainers_changed = (stock_info->get_price_change_percent() > 0.0 && position < s_top_stocks_list_size);
    top_losers_changed = (stock_info->get_price_change_percent() < 0.0 &&
      static_cast<int32_t>(m_sorted_stocks.size()) - position <= s_top_stocks_list_size);
  } 
}

void Stocks_tracker::_update_stock_in_sorted_list(const shared_ptr<Stock_info>& stock_info, double new_price,
  bool& top_gainers_changed, bool& top_losers_changed)
{
  assert(stock_info != nullptr);
  assert(!m_sorted_stocks.empty());
  assert(new_price > 0.0);

  // Calculate price change for given stock.
  double new_price_change = Stock_info::calculate_price_change_percent(stock_info->get_first_price(), new_price);  

  int32_t removed_stock_position = s_invalid_index;
  int32_t inserted_stock_position = s_invalid_index;

  if (new_price_change <= m_sorted_stocks.back()->get_price_change_percent())
  { // Price change is less than price change of the last element in list (smallest price change).    

    removed_stock_position = _remove_stock_from_sorted_list(stock_info);

    // Add stock to the end of list.
    inserted_stock_position = m_sorted_stocks.size();
    m_sorted_stocks.push_back(stock_info); // exception
  }
  else
  { // Look for the place in list to insert new stock.

    int32_t position = -1;

    for (auto iterator = m_sorted_stocks.begin(); iterator != m_sorted_stocks.end(); iterator++)
    {
      position++;

      if (*iterator == stock_info)
      { // Previous position of this stock is found.

        removed_stock_position = position;

        // Remove stock from previous position.
        iterator = m_sorted_stocks.erase(iterator);
      } // else do nothing

      if (iterator != m_sorted_stocks.end())
      { // End of list is not reached.

        if (inserted_stock_position == s_invalid_index &&
          new_price_change > (*iterator)->get_price_change_percent())
        { // Found place for stock with updated price.

          m_sorted_stocks.insert(iterator, stock_info); // exception

          inserted_stock_position = position;
        }
      }
      else
      { // List is empty after removing this stock.

        // Insert this stock again.
        m_sorted_stocks.push_back(stock_info); // exception

        inserted_stock_position = position;
      }      

      if (removed_stock_position != s_invalid_index &&
        inserted_stock_position != s_invalid_index)
      {
        break;
      }
    } // for
  }  

  assert(removed_stock_position != s_invalid_index);
  assert(inserted_stock_position != s_invalid_index);

  double previous_price_change = stock_info->get_price_change_percent();

  // Update price of the stock.
  stock_info->update_price(new_price);

  top_gainers_changed = (previous_price_change > 0.0 && removed_stock_position < s_top_stocks_list_size) ||
     (new_price_change > 0.0 && inserted_stock_position < s_top_stocks_list_size);

  top_losers_changed = (previous_price_change < 0.0 && 
    (static_cast<int32_t>(m_sorted_stocks.size()) - removed_stock_position <= s_top_stocks_list_size) ||
    (new_price_change < 0.0 && 
     (static_cast<int32_t>(m_sorted_stocks.size()) - inserted_stock_position <= s_top_stocks_list_size)));
}

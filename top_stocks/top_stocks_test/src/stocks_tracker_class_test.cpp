////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stocks_tracker_class_test.cpp
/// @brief Test of Stocks_tracker class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "stocks_tracker_class_test.h"

using namespace std;

bool StocksTrackerClassTest::check_stocks_for_price_change_ascending_sort(const vector<shared_ptr<Stock_info>>& stocks)
{
  if (stocks.size() < 2)
  {
    return true;
  }

  bool sort_check_result = true;

  for (size_t i = 1; i < stocks.size() && sort_check_result; i++)
  {
    sort_check_result = (stocks[i - 1]->get_price_change_percent() <= stocks[i]->get_price_change_percent());
  }

  return sort_check_result;
}

bool StocksTrackerClassTest::check_stocks_for_price_change_descending_sort(const vector<shared_ptr<Stock_info>>& stocks)
{
  if (stocks.size() < 2)
  {
    return true;
  }

  bool sort_check_result = true;

  for (size_t i = 1; i < stocks.size() && sort_check_result; i++)
  {
    sort_check_result = (stocks[i - 1]->get_price_change_percent() >= stocks[i]->get_price_change_percent());
  }

  return sort_check_result;
}

bool StocksTrackerClassTest::compare_stocks_contents(const std::vector<std::shared_ptr<Stock_info>>& stocks_vector1,
  const std::vector<std::shared_ptr<Stock_info>>& stocks_vector2)
{
  if (stocks_vector1.size() != stocks_vector2.size())
  {
    return false;
  }

  bool result = true;

  for (size_t i = 0; i < stocks_vector1.size() && result; i++)
  {
    const shared_ptr<Stock_info>& stock1 = stocks_vector1[i];
    const shared_ptr<Stock_info>& stock2 = stocks_vector2[i];

    result = (stock1->get_id() == stock2->get_id() &&
      stock1->get_first_price() == stock2->get_first_price() &&
      stock1->get_last_price() == stock2->get_last_price());
  }

  return result;
}

void StocksTrackerClassTest::verify_gainers(const std::vector<std::shared_ptr<Stock_info>>& gainers_expected,
  const std::vector<std::shared_ptr<Stock_info>>& gainers_actual)
{  
  EXPECT_EQ(gainers_expected.size(), gainers_actual.size());

  if (gainers_expected.size() != gainers_actual.size())
  {
    return;
  }
  
  EXPECT_TRUE(compare_stocks_contents(gainers_expected, gainers_actual));

  EXPECT_TRUE(check_stocks_for_price_change_descending_sort(gainers_actual));
}

void StocksTrackerClassTest::verify_losers(const std::vector<std::shared_ptr<Stock_info>>& losers_expected,
  const std::vector<std::shared_ptr<Stock_info>>& losers_actual)
{
  EXPECT_EQ(losers_expected.size(), losers_actual.size());

  if (losers_expected.size() != losers_actual.size())
  {
    return;
  }

  EXPECT_TRUE(compare_stocks_contents(losers_expected, losers_actual));

  EXPECT_TRUE(check_stocks_for_price_change_ascending_sort(losers_actual));
}

TEST(StocksTrackerClassTest, VerifyOnQuoteInvalidArgument)
{
  Stocks_tracker stocks_tracker;

  EXPECT_THROW(stocks_tracker.on_quote(-1, 123.5), invalid_argument);
  EXPECT_THROW(stocks_tracker.on_quote(Stocks_tracker::s_max_stocks_count, 123.5), invalid_argument);
  EXPECT_THROW(stocks_tracker.on_quote(0, 0.0), invalid_argument);
  EXPECT_THROW(stocks_tracker.on_quote(0, -1.0), invalid_argument);
}

TEST(StocksTrackerClassTest, VerifyStocksTracker)
{
  Stocks_tracker stocks_tracker;

  shared_ptr<Top_stocks_listener> top_stocks_listener = make_shared<Top_stocks_listener_impl>();
  Top_stocks_listener_impl* top_stocks_listener_impl = (Top_stocks_listener_impl*)top_stocks_listener.get();

  stocks_tracker.set_top_stocks_listener(top_stocks_listener);

  EXPECT_EQ(0, stocks_tracker.top_gainers().size());
  EXPECT_EQ(0, stocks_tracker.top_losers().size());           

  vector<shared_ptr<Stock_info>> gainers_expected;
  vector<shared_ptr<Stock_info>> losers_expected;

  shared_ptr<Stock_info> stock1 = make_shared<Stock_info>(0, 12.5, 12.5);
  stocks_tracker.on_quote(stock1->get_id(), stock1->get_first_price());
  
  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  shared_ptr<Stock_info> stock2 = make_shared<Stock_info>(5, 44.5, 44.5);
  stocks_tracker.on_quote(stock2->get_id(), stock2->get_first_price());

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock1->update_price(12.6);
  gainers_expected = { stock1 };
  losers_expected = {};
  stocks_tracker.on_quote(stock1->get_id(), stock1->get_last_price());

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock2->update_price(44.4);
  gainers_expected = { stock1 };
  losers_expected = { stock2 };
  stocks_tracker.on_quote(stock2->get_id(), stock2->get_last_price());

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  shared_ptr<Stock_info> stock3 = make_shared<Stock_info>(6, 12.7, 12.7);
  stocks_tracker.on_quote(stock3->get_id(), stock3->get_first_price());

  stock3->update_price(15.0);
  gainers_expected = { stock3, stock1 };
  losers_expected = { stock2 };
  stocks_tracker.on_quote(stock3->get_id(), stock3->get_last_price());

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  shared_ptr<Stock_info> stock4 = make_shared<Stock_info>(7, 14.0, 14.0);
  stocks_tracker.on_quote(stock4->get_id(), stock4->get_first_price());

  stock4->update_price(14.01);
  gainers_expected = { stock3, stock1, stock4 };
  losers_expected = { stock2 };
  stocks_tracker.on_quote(stock4->get_id(), stock4->get_last_price());

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  shared_ptr<Stock_info> stock5 = make_shared<Stock_info>(8, 2.0, 2.0);
  stocks_tracker.on_quote(stock5->get_id(), stock5->get_first_price());

  stock5->update_price(2.3);
  gainers_expected = { stock3, stock5, stock1, stock4 };
  losers_expected = { stock2 };
  stocks_tracker.on_quote(stock5->get_id(), stock5->get_last_price());

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  shared_ptr<Stock_info> stock6 = make_shared<Stock_info>(9, 2.0, 2.0);
  stocks_tracker.on_quote(stock6->get_id(), stock6->get_first_price());

  shared_ptr<Stock_info> stock7 = make_shared<Stock_info>(10, 7.0, 7.0);
  stocks_tracker.on_quote(stock7->get_id(), stock7->get_first_price());

  shared_ptr<Stock_info> stock8 = make_shared<Stock_info>(11, 10.0, 10.0);
  stocks_tracker.on_quote(stock8->get_id(), stock8->get_first_price());

  shared_ptr<Stock_info> stock9 = make_shared<Stock_info>(12, 30.0, 30.0);
  stocks_tracker.on_quote(stock9->get_id(), stock9->get_first_price());

  shared_ptr<Stock_info> stock10 = make_shared<Stock_info>(13, 5.0, 5.0);
  stocks_tracker.on_quote(stock10->get_id(), stock10->get_first_price());

  shared_ptr<Stock_info> stock11 = make_shared<Stock_info>(9999, 23.0, 23.0);
  stocks_tracker.on_quote(stock11->get_id(), stock11->get_first_price());

  gainers_expected = { stock3, stock5, stock1, stock4 };
  losers_expected = { stock2 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock6->update_price(2.5);
  stocks_tracker.on_quote(stock6->get_id(), stock6->get_last_price());

  stock7->update_price(10.0);
  stocks_tracker.on_quote(stock7->get_id(), stock7->get_last_price());

  stock8->update_price(15.0);
  stocks_tracker.on_quote(stock8->get_id(), stock8->get_last_price());

  stock9->update_price(48.0);
  stocks_tracker.on_quote(stock9->get_id(), stock9->get_last_price());

  stock10->update_price(9.0);
  stocks_tracker.on_quote(stock10->get_id(), stock10->get_last_price());

  stock11->update_price(46.0);
  stocks_tracker.on_quote(stock11->get_id(), stock11->get_last_price());

  gainers_expected = { stock11, stock10, stock9, stock8, stock7, stock6, stock3, stock5, stock1, stock4 };
  losers_expected = { stock2 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  shared_ptr<Stock_info> stock12 = make_shared<Stock_info>(1000, 40.0, 40.0);
  stocks_tracker.on_quote(stock12->get_id(), stock12->get_first_price());

  stock12->update_price(120.0);
  stocks_tracker.on_quote(stock12->get_id(), stock12->get_last_price());

  gainers_expected = { stock12, stock11, stock10, stock9, stock8, stock7, stock6, stock3, stock5, stock1 };
  losers_expected = { stock2 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock4->update_price(13.0);
  stocks_tracker.on_quote(stock4->get_id(), stock4->get_last_price());

  gainers_expected = { stock12, stock11, stock10, stock9, stock8, stock7, stock6, stock3, stock5, stock1 };
  losers_expected = { stock4, stock2 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock12->update_price(39.99);
  stocks_tracker.on_quote(stock12->get_id(), stock12->get_last_price());

  gainers_expected = { stock11, stock10, stock9, stock8, stock7, stock6, stock3, stock5, stock1 };
  losers_expected = { stock4, stock2, stock12 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());  

  shared_ptr<Stock_info> stock13 = make_shared<Stock_info>(500, 1.0, 1.0);
  stocks_tracker.on_quote(stock13->get_id(), stock13->get_first_price());

  shared_ptr<Stock_info> stock14 = make_shared<Stock_info>(2016, 5.0, 5.0);
  stocks_tracker.on_quote(stock14->get_id(), stock14->get_first_price());

  shared_ptr<Stock_info> stock15 = make_shared<Stock_info>(666, 100.0, 100.0);
  stocks_tracker.on_quote(stock15->get_id(), stock15->get_first_price());

  stock13->update_price(0.5);
  stocks_tracker.on_quote(stock13->get_id(), stock13->get_last_price());

  stock14->update_price(1.0);
  stocks_tracker.on_quote(stock14->get_id(), stock14->get_last_price());

  stock15->update_price(90.0);
  stocks_tracker.on_quote(stock15->get_id(), stock15->get_last_price());    

  stock10->update_price(4.99);
  stocks_tracker.on_quote(stock10->get_id(), stock10->get_last_price());

  stock7->update_price(5.00);
  stocks_tracker.on_quote(stock7->get_id(), stock7->get_last_price());

  stock3->update_price(12.00);
  stocks_tracker.on_quote(stock3->get_id(), stock3->get_last_price());

  gainers_expected = { stock11, stock9, stock8, stock6, stock5, stock1 };
  losers_expected = { stock14, stock13, stock7, stock15, stock4, stock3, stock2, stock10, stock12 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock5->update_price(0.1);
  stocks_tracker.on_quote(stock5->get_id(), stock5->get_last_price());

  gainers_expected = { stock11, stock9, stock8, stock6, stock1 };
  losers_expected = { stock5, stock14, stock13, stock7, stock15, stock4, stock3, stock2, stock10, stock12 };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stock1->update_price(2.0);
  stocks_tracker.on_quote(stock1->get_id(), stock1->get_last_price());

  gainers_expected = { stock11, stock9, stock8, stock6 };
  losers_expected = { stock5, stock1, stock14, stock13, stock7, stock15, stock4, stock3, stock2, stock10, };  

  stock9->update_price(40.0);
  stocks_tracker.on_quote(stock9->get_id(), stock9->get_last_price());

  stock14->update_price(4.0);
  stocks_tracker.on_quote(stock14->get_id(), stock14->get_last_price());

  gainers_expected = { stock11, stock8, stock9, stock6 };
  losers_expected = { stock5, stock1, stock13, stock7, stock14, stock15, stock4, stock3, stock2, stock10, };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());

  stocks_tracker.clear();

  gainers_expected = { };
  losers_expected = { };

  StocksTrackerClassTest::verify_gainers(gainers_expected, stocks_tracker.top_gainers());
  StocksTrackerClassTest::verify_losers(losers_expected, stocks_tracker.top_losers());
  EXPECT_TRUE(stocks_tracker.top_gainers() == top_stocks_listener_impl->get_top_gainers());
  EXPECT_TRUE(stocks_tracker.top_losers() == top_stocks_listener_impl->get_top_losers());
}

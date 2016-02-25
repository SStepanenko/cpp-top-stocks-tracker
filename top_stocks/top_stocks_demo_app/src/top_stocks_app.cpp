////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file top_stocks_app.cpp
/// @brief Implementation of the Top_stocks_app class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Top_stocks_app class members.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int32_t Top_stocks_app::s_max_price = 1000;

const int32_t Top_stocks_app::s_max_price_change_percent = 100;

const int32_t Top_stocks_app::s_stocks_update_fequency_milliseconds = 500;

const char Top_stocks_app::s_space_char = ' ';

const char Top_stocks_app::s_LF_char = '\n';

const string Top_stocks_app::s_top_gainers = "Top Gainers";

const string Top_stocks_app::s_top_losers = "Top Losers";

const string Top_stocks_app::s_table_rows_separator =
  "------------------------------------------------------------";

const string Top_stocks_app::s_table_columns_separator = " | ";

const string Top_stocks_app::s_stock_id_column = "Stock ID";

const string Top_stocks_app::s_first_price_column = "First Price ($)";

const string Top_stocks_app::s_last_price_column = "Last Price ($)";

const string Top_stocks_app::s_change_column = "Change (%)";

const int32_t Top_stocks_app::s_top_stocks_table_rows_count = 10;

const uint32_t Top_stocks_app::s_floating_point_output_precision = 2;

const uint32_t Top_stocks_app::s_column_width = 11;

Top_stocks_app::Top_stocks_app() : m_is_running(false)
{
  srand(static_cast<unsigned int>(time(0)));
}

Top_stocks_app::~Top_stocks_app()
{

}

void Top_stocks_app::run()
{
  m_is_running = true;

  while (m_is_running)
  {
    _update_stocks();

    _clear_screen();

    _output_top_stocks_tables(cout);

    this_thread::sleep_for(chrono::milliseconds(s_stocks_update_fequency_milliseconds));
  }  
}

void Top_stocks_app::terminate()
{
  m_is_running = false;
}

int32_t Top_stocks_app::_generate_stock_id()
{
  int32_t stock_id = rand() % Stocks_tracker::s_max_stocks_count;

  return stock_id;
}

double Top_stocks_app::_generate_price_change_percent()
{
  // Integer part of price change.
  double price_change_integer_part = static_cast<double>(rand() % 100);

  // Generate fractional part in the range [0, 99].
  double price_change_fractional_part = static_cast<double>(rand() % 100);

  // Multiplier of sign: +1 or -1.
  double sign_multiplier = (rand() % 2 == 0 ? 1.0 : -1.0);

  // Price change percent.
  double price_change_percent = (price_change_integer_part + (price_change_fractional_part / 100.0)) * sign_multiplier;

  return price_change_percent;
}

double Top_stocks_app::_generate_price(double first_price)
{
  assert(first_price >= 0.0);

  double price = 0.0;

  if (first_price == 0.0)
  {
    price = static_cast<double>(rand() % (s_max_price + 1));
  }
  else
  {
    double price_change_percent = _generate_price_change_percent();

    assert(price_change_percent < 100.0);

    price = first_price + first_price * (price_change_percent / 100.0);    
  }

  assert(price > 0.0);

  return price;
}

void Top_stocks_app::_clear_screen()
{
  system("cls");
}

void Top_stocks_app::_output_string_field(const string& field_value, int32_t column_width,
  ostream& output_stream)
{
  assert(column_width > 0);

  output_stream << setw(column_width) << left;

  output_stream << field_value << s_table_columns_separator;
}

void Top_stocks_app::_output_integer_field(int32_t field_value, int32_t column_width, std::ostream& output_stream)
{
  assert(column_width > 0);

  output_stream << setw(column_width) << noshowpos << left;

  output_stream << field_value << s_table_columns_separator;
}

void Top_stocks_app::_output_double_field(double field_value, int32_t column_width, ostream& output_stream)
{
  assert(column_width > 0);

  output_stream << setiosflags(ios::fixed)
    << setprecision(s_floating_point_output_precision)
    << setw(column_width)
    << noshowpos
    << left;

  output_stream << field_value << s_table_columns_separator;
}

void Top_stocks_app::_output_double_field_with_sign(double field_value, int32_t column_width, ostream& output_stream)
{
  assert(column_width > 0);

  output_stream << setiosflags(ios::fixed)
    << setprecision(s_floating_point_output_precision)
    << setw(column_width)
    << showpos
    << left;

  output_stream << field_value << s_table_columns_separator;
}

void Top_stocks_app::_output_top_stocks_table_fields(std::ostream& output_stream)
{
  output_stream << s_table_columns_separator;

  _output_string_field(s_stock_id_column, s_stock_id_column.size(), output_stream);

  _output_string_field(s_first_price_column, s_first_price_column.size(), output_stream);

  _output_string_field(s_last_price_column, s_last_price_column.size(), output_stream);

  _output_string_field(s_change_column, s_change_column.size(), output_stream);
}

void Top_stocks_app::_output_top_stocks_table_row(const shared_ptr<Stock_info>& stock_info, ostream& output_stream)
{
  assert(stock_info != nullptr);

  output_stream << s_table_columns_separator;

  _output_integer_field(stock_info->get_id(), s_stock_id_column.size(), output_stream);

  _output_double_field(stock_info->get_first_price(), s_first_price_column.size(), output_stream);

  _output_double_field(stock_info->get_last_price(), s_last_price_column.size(), output_stream);

  _output_double_field_with_sign(stock_info->get_price_change_percent(), s_change_column.size(), output_stream);
}

void Top_stocks_app::_output_top_stocks_table_empty_row(ostream& output_stream)
{
  output_stream << s_table_columns_separator;

  string empty_string;

  _output_string_field(empty_string, s_stock_id_column.size(), output_stream);

  _output_string_field(empty_string, s_first_price_column.size(), output_stream);

  _output_string_field(empty_string, s_last_price_column.size(), output_stream);

  _output_string_field(empty_string, s_change_column.size(), output_stream);  
}

void Top_stocks_app::_update_stocks()
{
  int32_t stock_id = _generate_stock_id();

  const shared_ptr<Stock_info>& stock_info = m_stocks_tracker.stocks()[stock_id];

  double first_price = (stock_info != nullptr ? stock_info->get_first_price() : 0.0);

  double new_price = _generate_price(first_price);

  assert(new_price > 0.0);

  m_stocks_tracker.on_quote(stock_id, new_price); // exception

  first_price = new_price;

  new_price = _generate_price(first_price);

  assert(new_price > 0.0);

  m_stocks_tracker.on_quote(stock_id, new_price); // exception
}

void Top_stocks_app::_output_top_stocks_tables(ostream& output_stream)
{  
  // Top gainers caption.
  output_stream << s_space_char;
  output_stream << setw(s_table_rows_separator.size() + 1) << left << s_top_gainers;
  
  // Top losers caption.
  output_stream << s_space_char;
  output_stream << s_top_losers << s_LF_char;

  // Rows separator for gainers.
  output_stream << s_space_char << s_table_rows_separator;

  output_stream << s_space_char;

  // Rows separator for losers.
  output_stream << s_space_char << s_table_rows_separator << s_LF_char;

  // Fields for gainers.
  _output_top_stocks_table_fields(output_stream);

  // Fields for losers.
  _output_top_stocks_table_fields(output_stream);

  output_stream << s_LF_char;

  // Rows separator for gainers.
  output_stream << s_space_char << s_table_rows_separator;

  output_stream << s_space_char;

  // Rows separator for losers.
  output_stream << s_space_char << s_table_rows_separator << s_LF_char;

  // Output top gainers and losers.
  for (int32_t i = 0; i < s_top_stocks_table_rows_count; i++)
  {
    // Output top gainer.
    if (i < static_cast<int32_t>(m_stocks_tracker.top_gainers().size()))
    {
      _output_top_stocks_table_row(m_stocks_tracker.top_gainers()[i], output_stream);
    }
    else
    {
      _output_top_stocks_table_empty_row(output_stream);
    }

    // Output top loser.
    if (i < static_cast<int32_t>(m_stocks_tracker.top_losers().size()))
    {
      _output_top_stocks_table_row(m_stocks_tracker.top_losers()[i], output_stream);
    }
    else
    {
      _output_top_stocks_table_empty_row(output_stream);
    }

    output_stream << s_LF_char;

    // Rows separator for gainers.
    output_stream << s_space_char << s_table_rows_separator;

    output_stream << s_space_char;

    // Rows separator for losers.
    output_stream << s_space_char << s_table_rows_separator << s_LF_char;
  } // for
}

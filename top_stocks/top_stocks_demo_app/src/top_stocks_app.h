////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file top_stocks_app.h
/// @brief Interface of the Top_stock_app class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TOP_STOCKS_APP_H_CAFA8DFC_53CB_4167_8C47_841A390A74A0
#define TOP_STOCKS_APP_H_CAFA8DFC_53CB_4167_8C47_841A390A74A0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class Top_stocks_app: represents top stocks application.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Top_stocks_app final
{
public:
   
  // Public methods.

  /// @brief Constructor.
  Top_stocks_app();

  /// @brief Destructor.
  ~Top_stocks_app();

  /// @brief Runs application.
  /// @exception bad_alloc
  /// @exception invalid_argument
  void run();

  /// @brief Terminates application.
  void terminate();

private:

  // Private static methods.

  // Generates stock ID in the range [0; 9999].
  static int32_t _generate_stock_id();

  // Generates price change percent in the range [0.0; 99.99] (can be positive or negative).
  static double _generate_price_change_percent();

  // Generates price: 1) If first price is equal to 0.0 then price is generated in the range [1.0; 1000].
  //                  2) Otherwise function generates price change percent and modifies base price using this value. 
  // param first_price First price.
  static double _generate_price(double first_price);

  // Clears screen.
  static void _clear_screen();

  // Outputs string field.
  // param field_value Field value.
  // param column_width Table column width.
  // param output_stream Output stream.
  static void _output_string_field(const std::string& field_value, int32_t column_width, std::ostream& output_stream);

  // Outputs integer field.
  // param field_value Field value.
  // param column_width Table column width.
  // param output_stream Output stream.
  static void _output_integer_field(int32_t field_value, int32_t column_width, std::ostream& output_stream);
  
  // Outputs double field.
  // param field_value Field value.
  // param column_width Table column width.
  // param output_stream Output stream.
  static void _output_double_field(double field_value, int32_t column_width, std::ostream& output_stream);

  // Outputs double field with sign (+ or -).
  // param field_value Field value.
  // param column_width Table column width.
  // param output_stream Output stream.
  static void _output_double_field_with_sign(double field_value, int32_t column_width, std::ostream& output_stream);

  // Outputs top stocks tables fields (tables headers).
  // param output_stream Output stream.
  static void _output_top_stocks_table_fields(std::ostream& output_stream);

  // Outputs one row of top stocks table.
  // param stock_info Stock info.
  // param output_stream Output stream.
  static void _output_top_stocks_table_row(const std::shared_ptr<Stock_info>& stock_info, std::ostream& output_stream);

  // Outputs empty row of top stocks table.
  // param output_stream Output stream.
  static void _output_top_stocks_table_empty_row(std::ostream& output_stream);

  // Private methods.

  // Private copy constructor without implementation to prohibit using it.
  Top_stocks_app(const Top_stocks_app&);

  // Private assignment operator without implementation to prohibit using it.
  Top_stocks_app& operator=(const Top_stocks_app&);

  // Updates stocks data (generates stock ID and new price for it).
  void _update_stocks();

  // Outputs top stocks tables.
  // param output_stream Output stream.
  void _output_top_stocks_tables(std::ostream& output_stream);

  // Private static constants.  

  static const int32_t s_max_price;

  static const int32_t s_max_price_change_percent;

  static const int32_t s_stocks_update_fequency_milliseconds;

  static const char s_space_char;

  static const char s_LF_char;

  static const std::string s_top_gainers;

  static const std::string s_top_losers;

  static const std::string s_table_rows_separator;

  static const std::string s_table_columns_separator;

  static const std::string s_stock_id_column;

  static const std::string s_first_price_column;

  static const std::string s_last_price_column;

  static const std::string s_change_column;

  static const int32_t s_top_stocks_table_rows_count;

  static const uint32_t s_floating_point_output_precision;

  static const uint32_t s_column_width;

  // Private fields.
  
  Stocks_tracker m_stocks_tracker; // Stocks tracker.

  bool m_is_running; // Flag defines whether application is running or not.

}; // class Stock_info

#endif // TOP_STOCKS_APP_H_CAFA8DFC_53CB_4167_8C47_841A390A74A0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stock_info.h
/// @brief Interface of the Stock_info class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STOCK_INFO_H_2C83B997_8DC3_442E_A30A_1FF3CBC4E29C
#define STOCK_INFO_H_2C83B997_8DC3_442E_A30A_1FF3CBC4E29C

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class Stock_info: represents stock info.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Stock_info final
{
public:

  // Public static methods.

  /// @brief Calculates price change percent.
  /// @param first_price First (base) price.
  /// @param last_price Last price.
  static double calculate_price_change_percent(double first_price, double last_price);

  // Public methods.

  /// @brief Constructor.
  /// @param stock_id Stock identifier.
  /// @param first_price First (base) price.
  /// @param last_price Last price.
  Stock_info(int32_t stock_id, double first_price, double last_price);

  /// @brief Destructor.
  ~Stock_info();

  /// @brief Gets stock identifier.
  int32_t get_id() const { return m_id; }

  /// @brief Gets first (base) price.
  double get_first_price() const { return m_first_price;  }

  /// @brief Gets last price.
  double get_last_price() const { return m_last_price; }

  /// @brief Updates price (last price).
  void update_price(double new_price);

  /// @brief Gets price change (between first and last price) percent.
  double get_price_change_percent() const { return m_price_change_percent; }

private:  

  // Private fields.

  // ID of stock.
  int32_t m_id;

  // First price.
  double m_first_price;

  // Last price.
  double m_last_price;

  // Price change percent.
  double m_price_change_percent;
}; // class Stock_info

#endif // STOCK_INFO_H_2C83B997_8DC3_442E_A30A_1FF3CBC4E29C

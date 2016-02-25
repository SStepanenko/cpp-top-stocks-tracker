////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file stocks_tracker.h
/// @brief Interface of the Stocks_tracker class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STOCKS_TRACKER_H_268124C1_DFF9_490A_B97D_BB149699CE08
#define STOCKS_TRACKER_H_268124C1_DFF9_490A_B97D_BB149699CE08


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class Stocks_tracker: tracker of stocks.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Stocks_tracker final
{
public:

  // Public methods.

  /// @brief Constructor.
  /// @exception bad_alloc
  Stocks_tracker();

  /// @brief Destructor.
  ~Stocks_tracker();

  /// @brief Gets map of stock ID to stock info.
  std::unordered_map<int32_t, std::shared_ptr<Stock_info>>& stocks() { return m_stocks_map; }

  /// @brief Gets list of top gainers (stocks with positive price change).
  const std::vector<std::shared_ptr<Stock_info>>& top_gainers() { return m_top_gainers; }

  /// @brief Gets list of top losers (stocks with negative price change).
  const std::vector<std::shared_ptr<Stock_info>>& top_losers() { return m_top_losers; }

  /// @brief Sets top stocks change listener.
  void set_top_stocks_listener(const std::shared_ptr<Top_stocks_listener>& top_stocks_listener)
  {
    m_top_stocks_listener = top_stocks_listener;
  }

  /// @brief Function called each time when price for some stock is changed.
  ///        New stock info is stored and if list of top gainers or list of top losers
  ///        is changed appropriate event is raised.
  /// @param stock_id Stock ID.
  /// @exception invalid_argument Invalid input argument.
  /// @exception bad_alloc.
  void on_quote(int32_t stock_id, double price);

  /// @brief Clears stocks info.
  void clear();

  // Public static constants.

  ///< Maximum stocks count
  static const int32_t s_max_stocks_count;

private:

  // Private methods.

  // Private copy constructor without implementation to prohibit using it.
  Stocks_tracker(const Stocks_tracker&);

  // Private assignment operator without implementation to prohibit using it.
  Stocks_tracker& operator=(const Stocks_tracker&);

  // Updates list of top gainers and raises event.
  void _update_top_gainers_and_raise_event();

  // Updates list of top losers and raises event.
  void _update_top_losers_and_raise_event();

  // Removes given stock from sorted list of stocks.
  // Given stock info should be in list.
  // param stock_info Stock info to be removed.
  // return Position of removed element.
  int32_t _remove_stock_from_sorted_list(const std::shared_ptr<Stock_info>& stock_info);

  // Inserts new stock in sorted list of stocks.
  // param stock_info Stock info to be inserted.
  // param [out] top_gainers_changed Flag defines if top gainers list is changed.
  // param [out] top_losers_changed Flag defines if top losers list is changed.
  // exception bad_alloc
  void _insert_new_stock_in_sorted_list(const std::shared_ptr<Stock_info>& stock_info,
    bool& top_gainers_changed, bool& top_losers_changed);  

  // Updates given stock info in sorted list: removes existed element, updates it's price 
  // and inserts in appropriate new position.
  // param stock_info Stock info to be updated.
  // param new_price New price of given stock.
  // param [out] top_gainers_changed Flag defines if top gainers list is changed.
  // param [out] top_losers_changed Flag defines if top losers list is changed.
  // exception bad_alloc
  void _update_stock_in_sorted_list(const std::shared_ptr<Stock_info>& stock_info, double new_price,
    bool& top_gainers_changed, bool& top_losers_changed);

  // Private static constants.

  // Size of top stocks list.
  static const int32_t s_top_stocks_list_size;

  // Invalid index of element in container.
  static const int32_t s_invalid_index;

  // Private fields.

  // Map of stock info to stock ID.
  std::unordered_map<int32_t, std::shared_ptr<Stock_info>> m_stocks_map;

  // Sorted in price change descending order list of stocks.
  std::list<std::shared_ptr<Stock_info>> m_sorted_stocks;

  // Top gainers (stocks with positive price change).
  std::vector<std::shared_ptr<Stock_info>> m_top_gainers;

  // Top losers (stocks with negative price change).
  std::vector<std::shared_ptr<Stock_info>> m_top_losers;

  // Listener of top (gainers / losers) lists change event.
  std::shared_ptr<Top_stocks_listener> m_top_stocks_listener;
}; // class Stocks_tracker

#endif // STOCKS_TRACKER_H_268124C1_DFF9_490A_B97D_BB149699CE08

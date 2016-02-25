////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file top_stocks_listener.h
/// @brief Top_stocks_listener interface.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TOP_STOCKS_LISTENER_H_7EDE8B49_E2F4_42BA_94A2_B58C832B56AA
#define TOP_STOCKS_LISTENER_H_7EDE8B49_E2F4_42BA_94A2_B58C832B56AA


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Top_stocks_listener: listener of top gainers / losers change event.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Top_stocks_listener
{
public:

  /// @brief Destructor.
  virtual ~Top_stocks_listener() = default;

  /// @brief Function called when top gainers list is changed.
  /// @param top_gainers List of top gainers.
  virtual void on_top_gainers_change(const std::vector<std::shared_ptr<Stock_info>>& top_gainers) = 0;

  /// @brief Function called when top losers list is changed.
  /// @param top_losers List of top losers.
  virtual void on_top_losers_change(const std::vector<std::shared_ptr<Stock_info>>& top_losers) = 0;  
  
}; // class Top_stocks_listener

#endif // TOP_STOCKS_LISTENER_H_7EDE8B49_E2F4_42BA_94A2_B58C832B56AA

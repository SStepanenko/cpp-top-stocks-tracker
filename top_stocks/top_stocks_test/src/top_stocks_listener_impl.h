////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file top_stocks_listener_impl.h
/// @brief Interface of the Top_stocks_listener_impl class.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TOP_STOCKS_LISTENER_IMPL_H
#define TOP_STOCKS_LISTENER_IMPL_H

#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Top_stocks_listener_impl: implements Top_stocks_listener interface.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Top_stocks_listener_impl final : public Top_stocks_listener
{
public:

  Top_stocks_listener_impl();

  virtual ~Top_stocks_listener_impl();

  /// @brief Function called when top gainers list is changed.
  /// @param top_gainers List of top gainers.
  virtual void on_top_gainers_change(const std::vector<std::shared_ptr<Stock_info>>& top_gainers) override;

  /// @brief Function called when top losers list is changed.
  /// @param top_losers List of top losers.
  virtual void on_top_losers_change(const std::vector<std::shared_ptr<Stock_info>>& top_losers) override;

  /// @brief Gets top gainers.
  const std::vector<std::shared_ptr<Stock_info>>& get_top_gainers() const { return m_top_gainers; }

  /// @brief Gets top losers.
  const std::vector<std::shared_ptr<Stock_info>>& get_top_losers() const { return m_top_losers; }

private:

  // Top gainers.
  std::vector<std::shared_ptr<Stock_info>> m_top_gainers;

  // Top losers.
  std::vector<std::shared_ptr<Stock_info>> m_top_losers;

}; // class Top_stocks_listener_impl

#endif // TOP_STOCKS_LISTENER_IMPL_H

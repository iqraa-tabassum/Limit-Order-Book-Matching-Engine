*** Limit Order Book / Matching Engine in C++
Built a limit order book and matching engine in C++ supporting price-time priority matching, partial fills, order cancellation and trade history.

Features:
Place BUY / SELL limit orders
- Automatic matching with partial fills
- Cancel pending orders
- Trade history and live order book display

How it works:
- User enters an order (e.g. BUY 50 100).
- The engine checks the best opposite order (lowest SELL for a BUY).
- If the prices match, a trade executes at the resting order's price.
- Any remaining quantity is saved in the order book (partial fill).
- Orders can be cancelled, and the book and trade history can be displayed.

What was used:
- C++ for the whole project
- std::map keeps price levels sorted
- std::list holds a FIFO queue of orders at each price (time priority)
- std::unordered_map stores each order's location for O(1) cancellation
- std::vector stores trade history
- Structs and classes: Order, Trade, OrderBook, MatchingEngine
- Integer prices to avoid floating-point errors
- g++, VS Code

Example:
> SELL 30 100
> BUY 50 100
  TRADE: buy #2 <-> sell #1 | 30 @ Rs 100.00


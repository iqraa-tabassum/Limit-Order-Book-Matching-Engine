# Order_Book
Limit Order Book &amp; Matching Engine in C++ with price-time priority, partial fills, order cancellation and trade history.
# Limit Order Book / Matching Engine in C++

A console-based trading simulation that matches buy/sell orders automatically using **price-time priority**.

## Features
- Place BUY / SELL limit orders
- Automatic matching with partial fills
- Cancel pending orders
- Trade history and live order book display

## Build and run
```
g++ -std=c++14 main.cpp OrderBook.cpp MatchingEngine.cpp -o orderbook
./orderbook          # Windows: .\orderbook.exe
```

## Commands
```
BUY <qty> <price>
SELL <qty> <price>
CANCEL <order_id>
BOOK
TRADES
EXIT
```

## Example
```
> SELL 30 100
> BUY 50 100
  TRADE: buy #2 <-> sell #1 | 30 @ Rs 100.00
```

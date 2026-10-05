#pragma once
#include "types.h"
#include <functional>
#include <list>
#include <map>
#include <unordered_map>

// Stores all pending orders.
// Each price level is a FIFO list  -> time priority
// Levels are sorted in a map       -> price priority
class OrderBook {
public:
    void  add(const Order& o);
    bool  cancel(uint64_t id);

    bool   hasBest(Side s) const;
    Order& bestOrder(Side s);      // front order of best price level
    void   removeBest(Side s);     // remove that order (fully filled)

    void display() const;

private:
    struct Loc { Side side; int64_t price; std::list<Order>::iterator pos; };

    std::map<int64_t, std::list<Order>, std::greater<int64_t>> bids_; // highest first
    std::map<int64_t, std::list<Order>>                        asks_; // lowest first
    std::unordered_map<uint64_t, Loc> index_;                         // O(1) cancel lookup
};

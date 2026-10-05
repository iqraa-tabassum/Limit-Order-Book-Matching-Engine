#pragma once
#include "OrderBook.h"
#include <vector>

class MatchingEngine {
public:
    // User Order -> Price Check -> Trade Execute -> remaining qty into Order Book
    std::vector<Trade> submit(Side side, int64_t price, int64_t qty);
    bool cancel(uint64_t id) { return book_.cancel(id); }

    uint64_t lastOrderId() const { return nextId_ - 1; }
    const std::vector<Trade>& trades() const { return trades_; }
    const OrderBook& book() const { return book_; }

private:
    OrderBook          book_;
    std::vector<Trade> trades_;
    uint64_t           nextId_ = 1;
    uint64_t           seq_    = 0;
};

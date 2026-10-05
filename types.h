#pragma once
#include <cstdint>

enum class Side { BUY, SELL };

// Prices are stored in paise (integer) to avoid floating-point errors.
// Rs 100.50 -> 10050
struct Order {
    uint64_t id;
    Side     side;
    int64_t  price;
    int64_t  qty;     // remaining quantity
    uint64_t seq;     // arrival sequence (time priority)
};

struct Trade {
    uint64_t buyId;
    uint64_t sellId;
    int64_t  price;   // price of the resting (older) order
    int64_t  qty;
};

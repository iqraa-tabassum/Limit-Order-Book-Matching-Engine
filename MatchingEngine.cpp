#include "MatchingEngine.h"
#include <algorithm>

std::vector<Trade> MatchingEngine::submit(Side side, int64_t price, int64_t qty) {
    Order in{nextId_++, side, price, qty, seq_++};
    std::vector<Trade> out;
    const Side opp = (side == Side::BUY) ? Side::SELL : Side::BUY;

    while (in.qty > 0 && book_.hasBest(opp)) {
        Order& rest = book_.bestOrder(opp);               // best price, oldest first

        bool priceOk = (side == Side::BUY) ? in.price >= rest.price
                                           : in.price <= rest.price;
        if (!priceOk) break;                              // Match? No -> save in book

        int64_t q = std::min(in.qty, rest.qty);           // partial matching
        Trade t{ side == Side::BUY ? in.id : rest.id,
                 side == Side::BUY ? rest.id : in.id,
                 rest.price, q };                         // trade at resting order's price
        out.push_back(t);
        trades_.push_back(t);

        in.qty   -= q;
        rest.qty -= q;
        if (rest.qty == 0) book_.removeBest(opp);
    }

    if (in.qty > 0) book_.add(in);                        // remaining quantity -> Order Book
    return out;
}

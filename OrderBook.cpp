#include "OrderBook.h"
#include <cstdio>
#include <iterator>
#include <vector>

void OrderBook::add(const Order& o) {
    if (o.side == Side::BUY) {
        auto& lvl = bids_[o.price];
        lvl.push_back(o);
        index_[o.id] = {o.side, o.price, std::prev(lvl.end())};
    } else {
        auto& lvl = asks_[o.price];
        lvl.push_back(o);
        index_[o.id] = {o.side, o.price, std::prev(lvl.end())};
    }
}

bool OrderBook::cancel(uint64_t id) {
    auto it = index_.find(id);
    if (it == index_.end()) return false;
    Loc loc = it->second;
    if (loc.side == Side::BUY) {
        auto lv = bids_.find(loc.price);
        lv->second.erase(loc.pos);
        if (lv->second.empty()) bids_.erase(lv);
    } else {
        auto lv = asks_.find(loc.price);
        lv->second.erase(loc.pos);
        if (lv->second.empty()) asks_.erase(lv);
    }
    index_.erase(it);
    return true;
}

bool OrderBook::hasBest(Side s) const {
    return s == Side::BUY ? !bids_.empty() : !asks_.empty();
}

Order& OrderBook::bestOrder(Side s) {
    return s == Side::BUY ? bids_.begin()->second.front()
                          : asks_.begin()->second.front();
}

void OrderBook::removeBest(Side s) {
    if (s == Side::BUY) {
        auto lv = bids_.begin();
        index_.erase(lv->second.front().id);
        lv->second.pop_front();
        if (lv->second.empty()) bids_.erase(lv);
    } else {
        auto lv = asks_.begin();
        index_.erase(lv->second.front().id);
        lv->second.pop_front();
        if (lv->second.empty()) asks_.erase(lv);
    }
}

void OrderBook::display() const {
    std::printf("\n========== ORDER BOOK ==========\n");
    std::printf("  SELL (asks)\n");
    std::vector<std::map<int64_t, std::list<Order>>::const_iterator> v;
    for (auto it = asks_.begin(); it != asks_.end(); ++it) v.push_back(it);
    if (v.empty()) std::printf("    (empty)\n");
    for (auto r = v.rbegin(); r != v.rend(); ++r) {
        int64_t total = 0;
        for (auto& o : (*r)->second) total += o.qty;
        std::printf("    Rs %9.2f | qty %6lld | orders:", (*r)->first / 100.0, (long long)total);
        for (auto& o : (*r)->second) std::printf(" #%llu(%lld)", (unsigned long long)o.id, (long long)o.qty);
        std::printf("\n");
    }
    std::printf("  ------------------------------\n");
    std::printf("  BUY (bids)\n");
    if (bids_.empty()) std::printf("    (empty)\n");
    for (auto& kv : bids_) {
        const int64_t price = kv.first;
        const std::list<Order>& lvl = kv.second;
        int64_t total = 0;
        for (auto& o : lvl) total += o.qty;
        std::printf("    Rs %9.2f | qty %6lld | orders:", price / 100.0, (long long)total);
        for (auto& o : lvl) std::printf(" #%llu(%lld)", (unsigned long long)o.id, (long long)o.qty);
        std::printf("\n");
    }
    std::printf("================================\n");
}
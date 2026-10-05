#include "MatchingEngine.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <algorithm>

static void printTrade(const Trade& t) {
    std::printf("  TRADE: buy #%llu <-> sell #%llu | %lld @ Rs %.2f\n",
                (unsigned long long)t.buyId, (unsigned long long)t.sellId,
                (long long)t.qty, t.price / 100.0);
}

static void help() {
    std::printf("Commands:\n"
                "  BUY <qty> <price>     e.g. BUY 100 100\n"
                "  SELL <qty> <price>    e.g. SELL 50 99.5\n"
                "  CANCEL <order_id>\n"
                "  BOOK                  show order book\n"
                "  TRADES                show trade history\n"
                "  HELP | EXIT\n");
}

int main() {
    MatchingEngine eng;
    std::printf("=== Limit Order Book / Matching Engine ===\n");
    help();

    std::string line;
    while (std::printf("\n> "), std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string cmd;
        if (!(ss >> cmd)) continue;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

        if (cmd == "BUY" || cmd == "SELL") {
            long long qty; double price;
            if (!(ss >> qty >> price) || qty <= 0 || price <= 0) {
                std::printf("  Usage: %s <qty> <price> (both > 0)\n", cmd.c_str());
                continue;
            }
            Side s = (cmd == "BUY") ? Side::BUY : Side::SELL;
            auto trades = eng.submit(s, (int64_t)std::llround(price * 100), qty);
            std::printf("  Order #%llu accepted: %s %lld @ Rs %.2f\n",
                        (unsigned long long)eng.lastOrderId(), cmd.c_str(), qty, price);
            for (auto& t : trades) printTrade(t);
            if (trades.empty()) std::printf("  No match - order saved in book.\n");
        } else if (cmd == "CANCEL") {
            unsigned long long id;
            if (!(ss >> id)) { std::printf("  Usage: CANCEL <order_id>\n"); continue; }
            std::printf(eng.cancel(id) ? "  Order #%llu cancelled.\n"
                                       : "  Order #%llu not found (filled or invalid).\n", id);
        } else if (cmd == "BOOK") {
            eng.book().display();
        } else if (cmd == "TRADES") {
            if (eng.trades().empty()) std::printf("  No trades yet.\n");
            for (auto& t : eng.trades()) printTrade(t);
        } else if (cmd == "HELP") {
            help();
        } else if (cmd == "EXIT" || cmd == "QUIT") {
            break;
        } else {
            std::printf("  Unknown command. Type HELP.\n");
        }
    }
    return 0;
}

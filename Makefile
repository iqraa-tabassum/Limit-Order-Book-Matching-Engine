CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
SRC      = main.cpp OrderBook.cpp MatchingEngine.cpp

orderbook: $(SRC) types.h OrderBook.h MatchingEngine.h
	$(CXX) $(CXXFLAGS) $(SRC) -o orderbook

clean:
	rm -f orderbook

CXXFLAGS = -std=c++23 -O3 -Wall -Wextra -Wpedantic -Ilib/OMPEval
LDLIBS = lib/OMPEval/lib/ompeval.a
OMPEVAL_NAME = ompeval
COMMON_SRC = src/utilities.cpp
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)
POKER_HAND_STRENGTHS_SRC = src/poker_hand_strengths.cpp $(COMMON_SRC)
POKER_HAND_STRENGTHS_OBJ = $(POKER_HAND_STRENGTHS_SRC:.cpp=.o)
POKER_HAND_STRENGTHS_NAME = poker-hand-strengths
POKER_EQUITIES_SRC = src/poker_equities.cpp $(COMMON_SRC)
POKER_EQUITIES_OBJ = $(POKER_EQUITIES_SRC:.cpp=.o)
POKER_EQUITIES_NAME = poker-equities
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
NAMES = $(POKER_HAND_STRENGTHS_NAME) $(POKER_EQUITIES_NAME)

.PHONY: all
all: $(NAMES)

.PHONY: $(OMPEVAL_NAME)
$(OMPEVAL_NAME):
	cd lib/OMPEval && $(MAKE)

$(POKER_HAND_STRENGTHS_NAME): $(POKER_HAND_STRENGTHS_OBJ) | $(OMPEVAL_NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(POKER_EQUITIES_NAME): $(POKER_EQUITIES_OBJ) | $(OMPEVAL_NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(NAMES)

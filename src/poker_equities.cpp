#include <iostream>
#include <sstream>

#include <omp/EquityCalculator.h>

#include "utilities.h"

int main(int argc, char* argv[])
{
	auto args = pokercmd::parse_args(argc, argv);
	auto equity_calculator = omp::EquityCalculator{};

	for (auto line = std::string{}; std::getline(std::cin, line);) {
		auto iss = std::istringstream{line};
		auto cards = std::string{};
		
		iss >> cards;

		if (cards == "-")
			cards.clear();

		auto board = omp::CardRange::getCardMask(cards);
		auto card_ranges = std::vector<omp::CardRange>{};

		while (iss >> cards)
			card_ranges.emplace_back(cards);

		if (args.standard_deviation)
			equity_calculator.start(
				card_ranges,
				board,
				0u,
				false,
				args.standard_deviation
			);
		else
			equity_calculator.start(card_ranges, board);

		equity_calculator.wait();

		auto results = equity_calculator.getResults();

		for (auto i = 0u; i < card_ranges.size(); ++i)
			std::cout << results.equity[i] << '\t';

		std::cout << std::endl;
	}

	return 0;
}

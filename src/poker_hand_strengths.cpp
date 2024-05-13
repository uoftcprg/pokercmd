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
		auto card_ranges = std::vector<omp::CardRange>{"random"};

		while (iss >> cards) {
			card_ranges.emplace_back(cards);

			if (args.duration)
				equity_calculator.start(
					card_ranges,
					board,
					0u,
					false,
					5e-5,
					[&args, &equity_calculator](
							const auto& r
					)
					{
						if (r.time >= args.duration)
						    equity_calculator.stop();
					},
					std::min(0.2, args.duration)
				);
			else
				equity_calculator.start(card_ranges, board);

			equity_calculator.wait();

			auto results = equity_calculator.getResults();

			std::cout << results.equity[1] << '\t';
			card_ranges.pop_back();
		}

		std::cout << std::endl;
	}

	return 0;
}

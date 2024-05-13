#include "utilities.h"

#include <cassert>
#include <iostream>

namespace pokercmd {

	Arguments parse_args(int argc, char* argv[])
	{
		assert(argc >= 1);

		auto args = Arguments{};

		if (argc >= 2)
			args.duration = std::stod(argv[1]);
		
		if (argc > 2) {
			(
				std::cout
				<< "Usage: "
				<< argv[0]
				<< " [duration]"
				<< std::endl
			);
			std::exit(1);
		}

		return args;
	}

}
